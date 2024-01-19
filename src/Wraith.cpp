#include "Wraith.h"
#include "Monster.h"
#include "Constants.h"
#include "Explosion.h"
#include "ThrowableRock.h"
#include "InstanceCount.h"
#include "Player.h"
#include "WraithAttack.h"
#include <random>
#include <string>
#include <vector>
#include <random>

using namespace std;

const string Wraith::FIRST_ASSET_PATH = "images/wraith_rightwalk/wraith_walk_right_1";
const int Wraith::WALK_ANIMATION_DELAY = 1;
const int Wraith::ATTACK_ANIMATION_DELAY = 4;
const int Wraith::ANIMATION_START_COUNT = 0;
const int Wraith::LAST_ASSET_INDEX = 11;
const int Wraith::ASSETS_SIZE = 12;
const int Wraith::DEFAULT_SPEED = 3;

Wraith::Wraith(int x, int y, int width, int height, int weight, GameEngine* engine) : 
            Monster(x, y, width, height, weight, DEFAULT_SPEED, constants::gResPath + FIRST_ASSET_PATH, engine),
            rightWalkAnimationHandler(WALK_ANIMATION_DELAY, ANIMATION_START_COUNT, LAST_ASSET_INDEX),
            leftWalkAnimationHandler(WALK_ANIMATION_DELAY, ANIMATION_START_COUNT, LAST_ASSET_INDEX),
            attackRightAnimationHandler(ATTACK_ANIMATION_DELAY, ANIMATION_START_COUNT, LAST_ASSET_INDEX, 1),
            attackLeftAnimationHandler(ATTACK_ANIMATION_DELAY, ANIMATION_START_COUNT, LAST_ASSET_INDEX, 1),
            life(START_LIFE)
{
    rightWalkAnimationHandler.addAssets(walkingRightAssetPaths, 1, ASSETS_SIZE, "images/wraith_rightwalk/wraith_walk_right_");
    leftWalkAnimationHandler.addAssets(walkingLeftAssetPaths, 1, ASSETS_SIZE, "images/wraith_leftwalk/wraith_walk_left_");
    attackRightAnimationHandler.addAssets(attackRightAssetPaths, 1, ASSETS_SIZE, "images/wraith_rightattack/wraith_attack_right_");
    attackLeftAnimationHandler.addAssets(attackLeftAssetPaths, 1, ASSETS_SIZE, "images/wraith_leftattack/wraith_attack_left_");
}

Wraith* Wraith::create(int x, int y, int width, int height, int weight, GameEngine *engine)
{
    return new Wraith(x, y, width, height, weight, engine);
}

void Wraith::tick()
{
    tickCounter++;
    handleWindowCollision(this);
    if (!animatingAttack)
    {
        handleMovement();
    }
    else 
    {
        animateAttack();
    }
    if ( (tickCounter % 600 == 0) && (InstanceCount<Monster>::getInstanceCount() < 30) )
    {
        spawn();
    }
}

void Wraith::spawn()
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distribution(-100, 100);
    int randomX = distribution(gen);
    int randomY = distribution(gen);
    getEngine()->addGameComponent(Wraith::create(this->getLeft() + randomX, this->getBottom() + randomY, 50, 70, 3, getEngine()));
}

void Wraith::handleMovement()
{
    if (Player* player = Player::getInstance())
    {
        int xDistance = player->getLeft() - getLeft();
        int yDistance = player->getTop() - getTop();
        if ( (xDistance < 300 && xDistance > -300) && (yDistance < 250 && yDistance > -250) )
        {
            moveTorwardPlayer();
        }
        else if (tickCounter % 30 == 0)
        {
            moveRandomly();
        }
    }
    animateWalking();
}

void Wraith::animateWalking()
{
    if ( (getXVelocity() > 0) && (rightWalkAnimationHandler.timeForNextAsset()) )
    {
        setTexture(constants::gResPath + walkingRightAssetPaths.at(rightWalkAnimationHandler.getAnimationCount()) + ".png");
    }
    else if ( (getXVelocity() < 0) && (leftWalkAnimationHandler.timeForNextAsset()) )
    {
        setTexture(constants::gResPath + walkingLeftAssetPaths.at(leftWalkAnimationHandler.getAnimationCount()) + ".png");
    }
}

void Wraith::handleCollision(const Component *other)
{
    if (dynamic_cast<const ThrowableRock *>(other))
    {
        life--;
        if (life <= 0)
        {
            getEngine()->removeGameComponent(this);
        }
    }

    if (dynamic_cast<const Player *>(other))
    {
        animatingAttack = true;
    }
}

void Wraith::animateAttack()
{  
    if ( (getXVelocity() > 0) && (attackRightAnimationHandler.timeForNextAsset()) )
    {
        setTexture(constants::gResPath + attackRightAssetPaths.at(attackRightAnimationHandler.getAnimationCount()) + ".png");
    }
    else if ( (getXVelocity() < 0) && (attackLeftAnimationHandler.timeForNextAsset()) )
    {
        setTexture(constants::gResPath + attackLeftAssetPaths.at(attackLeftAnimationHandler.getAnimationCount()) + ".png");
    }   

    if (attackRightAnimationHandler.timeForRemoval() || attackLeftAnimationHandler.timeForRemoval())
    {
        if (Player* player = Player::getInstance())
        {
            int attackSize = 120;
            int x = player->getPlayerXCenter() - (attackSize / 2);
            int y =  player->getPlayerYCenter() - (attackSize / 2);
            WraithAttack::create(x, y, attackSize, attackSize, 4, getEngine());
        }
        animatingAttack = false;
        attackRightAnimationHandler.resetValuesToOriginal();
        attackLeftAnimationHandler.resetValuesToOriginal();
    } 
}