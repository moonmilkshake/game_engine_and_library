#include "Player.h"
#include "Graphics.h"
#include "Constants.h"
#include "MovableSprite.h"
#include "ImmovableSprite.h"
#include "FireSpirit.h"
#include "ThrowableRock.h"
#include "GameEngine.h"
#include "PlayerElement.h"
#include "StoneElement.h"
#include "MagmaElement.h"
#include "IceElement.h"
#include "AttackDirection.h"
#include "PlayerAssets.h"
#include "StoneGolemAssets.h"
#include "MagmaGolemAssets.h"
#include "IceGolemAssets.h"
#include "ElementSwitch.h"
#include "Lightning.h"
#include "WraithAttack.h"
#include "IceBlob.h"
#include <functional>

/**
 * Singelton Class used to handle everything the user needs as player
 */
using namespace crane;

Player *Player::instance = nullptr;

Player::Player(int x, int y, int width, int height, int weight, std::string assetPath, GameEngine *eng) : 
        MovableSprite(x, y, width, height, weight, assetPath),
        engine(eng), life(DEFAULT_LIFE), throwPower(DEFAULT_POWER_LEVEL)
{
    setSpeed(DEFAULT_SPEED);
    assetsInstance = StoneGolemAssets::getInstance();
    elementInstance = StoneElement::getInstance();
    setUpPlayerUI();
}

Player *Player::create(int x, int y, int width, int height, int weight, std::string assetPath, GameEngine *engine)
{
    if (!instance)
    {
        instance = new Player(x, y, width, height, weight, assetPath, engine);
    }
    return instance;
}

void Player::setUpPlayerUI()
{
    int heartXPlacement = 15;
    int heartYPlacement = 15;
    for (int i = 0; i < 3; ++i)
    {
        MovableSprite* heart = MovableSprite::getInstance(heartXPlacement, heartYPlacement, 25, 25, 5,
                                constants::gResPath + assetsInstance->getHeartContainerAssetPath());
        heartContainers.push_back(heart);
        engine->addGameComponent(heart);
        heartXPlacement += 30;
    }
}

void Player::destroyInstance()
{
    if (instance)
    {
        delete instance;
        instance = nullptr;
    }
}

void Player::tick()
{
    handleTimeTracking();
    handleWindowCollision(this);

    setX(getLeft() + xVelocity);
    setY(getTop() + yVelocity);

    // Animate walking unless player is stationary
    if (xVelocity != 0 || yVelocity != 0)
    {
        animatePlayerWalking();
    }
}

void Player::updateCooldown(bool& isReady, int& timeTracker, int cooldownPeriod, std::function<void()> onReady)
{
    if (!isReady)
    {
        if (timeTracker >= cooldownPeriod)
        {
            isReady = true;
            if (onReady) onReady();
        }
        else
        {
            ++timeTracker;
        }
    }
}

void Player::handleTimeTracking()
{
    updateCooldown(specialAttackReady, specialAttackTimeTracker, SPECIAL_ATTACK_COOLDOWN_PERIOD, [this](){ animateSpecialAttackReady(); });
    updateCooldown(elementSwitchReady, elementSwitchTimeTracker, ELEMENT_SWITCH_COOLDOWN_PERIOD);
}

void Player::animateSpecialAttackReady()
{
    int width = 50;
    int height = getTop();
    int x = getPlayerXCenter() - (width / 2);
    int y = 20;
    Lightning::getInstance(x, y, width, height, 4, engine);
}

/**
 * Sets walking-texture based on players velocity
 */
void Player::animatePlayerWalking()
{
    setTexture(constants::gResPath + ((previousXVelocity > 0) ? 
                                        assetsInstance->getNextRightWalkAssetPath() : 
                                        assetsInstance->getNextLeftWalkAssetPath()));
}

/**
 * Handle necessary collisions (stopped from moving through ImmovableSprites, loses one life upon collision with Monster)
 */
void Player::handleCollision(const Component *other)
{
    if (const ImmovableSprite *immovableSpritePtr = dynamic_cast<const ImmovableSprite *>(other)) 
    {
        handleObstacleCollision(this, immovableSpritePtr);
    } 
    else if (dynamic_cast<const FireSpirit*>(other) && !(dynamic_cast<const MagmaElement*>(elementInstance))) 
    {
        takeDamage(1);
    }
    else if (const WraithAttack* attack = dynamic_cast<const WraithAttack*>(other))
    {
        if (!attack->getDamageDealt() && !(dynamic_cast<const StoneElement*>(elementInstance)))
        {
            takeDamage(1);
        }
    } 
    else if (dynamic_cast<const IceBlob*>(other) && !(dynamic_cast<const IceElement*>(elementInstance))) 
    {
        setSpeed(1);
    }
}

void Player::takeDamage(int damage)
{
    life-= damage;
    handleLifeDisplay();
    checkForDeath();
}

void Player::resetSpeed()
{
    setSpeed(DEFAULT_SPEED);
}

void Player::handleLifeDisplay()
{
    const std::string emptyHeartContainerPath = constants::gResPath + assetsInstance->getEmptyHeartContainerAssetPath();
    const std::string heartContainerPath = constants::gResPath + assetsInstance->getHeartContainerAssetPath();
    int amountOfHearts = heartContainers.size();

    for (int i = 0; i < amountOfHearts; ++i) 
    {
        heartContainers[i]->setTexture((i < life) ? heartContainerPath : emptyHeartContainerPath);
    }
}

void Player::checkForDeath()
{
    if (life == 0)
    {
        engine->removeGameComponent(this);
    }
}

/**
 * Sets up component for animating powerthrow if needed and animates the throw when called
 */

void Player::animatePowerThrowRight()
{
    setTexture(constants::gResPath + assetsInstance->getNextRightPowerThrowAssetPath());
}

void Player::animatePowerThrowLeft()
{
    setTexture(constants::gResPath + assetsInstance->getNextLeftPowerThrowAssetPath());
}

/**
 * Get middle of player X-plane
 */
int Player::getPlayerXCenter()
{
    return static_cast<int>(this->getLeft() + (this->getWidth() / 2));
}

/**
 * Get middle of player Y-plane
 */
int Player::getPlayerYCenter()
{
    return static_cast<int>(this->getTop() + (this->getHeight() / 2));
}

void Player::incrementThrowPower()
{
    throwPower++;
}

/**
 * Handles build-up of power-throw by incrementing the size of rock to be thrown and animates powering up
 */
void Player::handleUpArrowKeyDownPress()
{
    if (throwPower > DEFAULT_POWER_LEVEL + 5)
    {
        (previousXVelocity > 0) ? animatePowerThrowRight() : animatePowerThrowLeft();
    }
    incrementThrowPower();
}

void Player::handleDownArrowKeyDownPress()
{
    if (throwPower > DEFAULT_POWER_LEVEL + 5)
    {
        (previousXVelocity > 0) ? animatePowerThrowRight() : animatePowerThrowLeft();
    }
    incrementThrowPower();
}

void Player::handleLeftArrowKeyDownPress()
{
    if (throwPower > DEFAULT_POWER_LEVEL + 5)
    {
        animatePowerThrowLeft();
    }
    incrementThrowPower();
}

void Player::handleRightArrowKeyDownPress()
{
    if (throwPower > DEFAULT_POWER_LEVEL + 5)
    {
        animatePowerThrowRight();
    }
    incrementThrowPower();
}

void Player::handleSpaceKeyDownPress()
{
    if (specialAttackReady)
    {
        int attackStartX = getPlayerXCenter() - (throwPower / 2);
        int attackStartY = getPlayerYCenter() - (throwPower / 2);
        elementInstance->performSpecialAttack(throwPower, attackStartX, attackStartY, engine);
        specialAttackTimeTracker = 0;
        specialAttackReady = false;
    }
}

/**
 * Handling of rock-throwing
 */
void Player::handleUpArrowKeyUpRelease()
{
    setTexture(constants::gResPath + getCorrectStationaryAsset());
    initiateAttack(AttackDirection(Direction::Up));
}

void Player::handleDownArrowKeyUpRelease()
{
    setTexture(constants::gResPath + getCorrectStationaryAsset());
    initiateAttack(AttackDirection(Direction::Down));
}

void Player::handleLeftArrowKeyUpRelease()
{
    setTexture(constants::gResPath + assetsInstance->getStationaryLeftAssetPath());
    initiateAttack(AttackDirection(Direction::Left));
}

void Player::handleRightArrowKeyUpRelease()
{
    setTexture(constants::gResPath + assetsInstance->getStationaryRightAssetPath());
    initiateAttack(AttackDirection(Direction::Right));
}

void Player::initiateAttack(AttackDirection direction)
{
    elementInstance->performAttack(throwPower, direction, getPlayerXCenter(), getPlayerYCenter(), engine);
    resetAfterThrow();
}

/**
 * Resets necessary variables associated with throwing rocks as needed
 */
void Player::resetAfterThrow()
{
    throwPower = DEFAULT_POWER_LEVEL;
}

/**
 * Method that handles the moving of the player
 */
void Player::handleWKeyDownPress()
{
    yVelocity = -getSpeed();
}

void Player::handleSKeyDownPress()
{
    yVelocity = getSpeed();
}

void Player::handleAKeyDownPress()
{
    xVelocity = -getSpeed();
    previousXVelocity = -getSpeed();
}

void Player::handleDKeyDownPress()
{
    xVelocity = getSpeed();
    previousXVelocity = getSpeed();
}

const std::string Player::getCorrectStationaryAsset() const
{
    return (previousXVelocity > 0) ? assetsInstance->getStationaryRightAssetPath() : assetsInstance->getStationaryLeftAssetPath();
}

/**
 * Method that when player is to become stationary and sets texture in accordance to velocity before stopping
 */
void Player::handleWKeyRelease()
{
    setTexture(constants::gResPath + getCorrectStationaryAsset());
    if (yVelocity != getSpeed())
    {
        yVelocity = 0;
    }
}

void Player::handleSKeyRelease()
{
    setTexture(constants::gResPath + getCorrectStationaryAsset());
    if (yVelocity != -getSpeed())
    {
        yVelocity = 0;
    }
}

void Player::handleAKeyRelease()
{
    this->setTexture(constants::gResPath + assetsInstance->getStationaryLeftAssetPath());
    if (xVelocity != getSpeed())
    {
        xVelocity = 0;
    }
}

void Player::handleDKeyRelease()
{
    this->setTexture(constants::gResPath + assetsInstance->getStationaryRightAssetPath());
    if (xVelocity != -getSpeed())
    {
        xVelocity = 0;
    }
}

void Player::handleOneKeyDownPress()
{
    handleElementSwitch(StoneElement::getInstance(), StoneGolemAssets::getInstance());
}

void Player::handleTwoKeyDownPress()
{
    handleElementSwitch(MagmaElement::getInstance(), MagmaGolemAssets::getInstance());
}

void Player::handleThreeKeyDownPress()
{
    resetSpeed();
    handleElementSwitch(IceElement::getInstance(), IceGolemAssets::getInstance());
}

void Player::handleElementSwitch(PlayerElement* newElement, PlayerAssets* newAssets)
{
    if (elementSwitchReady)
    {
        initiateElementSwitchAnimation();
        elementInstance = newElement;
        assetsInstance = newAssets;
        setTexture(constants::gResPath + getCorrectStationaryAsset());
        elementSwitchTimeTracker = 0;
        elementSwitchReady = false;
    }    
}

void Player::initiateElementSwitchAnimation()
{
    int elementSwitchSize = 175;
    int elementSwitchX = getPlayerXCenter() - (elementSwitchSize / 2);
    int elementSwitchY = getPlayerYCenter() - (elementSwitchSize / 2);
    ElementSwitch::getInstance(elementSwitchX, elementSwitchY, elementSwitchSize, elementSwitchSize, 4, engine);
}

Player::~Player()
{
    StoneGolemAssets::getInstance()->destroyInstance();
    MagmaGolemAssets::getInstance()->destroyInstance();
    IceGolemAssets::getInstance()->destroyInstance();
}