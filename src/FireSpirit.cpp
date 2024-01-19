#include "FireSpirit.h"
#include "Monster.h"
#include "Constants.h"
#include "Explosion.h"
#include "FrostBite.h"
#include "InstanceCount.h"
#include <random>
#include <string>
#include <vector>

using namespace std;

const string FireSpirit::FIRST_ASSET_PATH = "images/firespirit_rightwalk/fire_spirit_walk_right_1";
const int FireSpirit::ANIMATION_DELAY = 2;
const int FireSpirit::ANIMATION_START_COUNT = 0;
const int FireSpirit::LAST_ASSET_INDEX = 5;
const int FireSpirit::ASSETS_SIZE = 6;
const int FireSpirit::DEFAULT_SPEED = 2;

FireSpirit::FireSpirit(int x, int y, int width, int height, int weight, GameEngine* engine) : 
            Monster(x, y, width, height, weight, DEFAULT_SPEED, constants::gResPath + FIRST_ASSET_PATH, engine),
            rightWalkAnimationHandler(ANIMATION_DELAY, ANIMATION_START_COUNT, LAST_ASSET_INDEX),
            leftWalkAnimationHandler(ANIMATION_DELAY, ANIMATION_START_COUNT, LAST_ASSET_INDEX) 
{
    rightWalkAnimationHandler.addAssets(walkingRightAssetPaths, 1, ASSETS_SIZE, "images/firespirit_rightwalk/fire_spirit_walk_right_");
    leftWalkAnimationHandler.addAssets(walkingLeftAssetPaths, 1, ASSETS_SIZE, "images/firespirit_leftwalk/fire_spirit_walk_left_");
}

FireSpirit* FireSpirit::create(int x, int y, int width, int height, int weight, GameEngine *engine)
{
    return new FireSpirit(x, y, width, height, weight, engine);
}

void FireSpirit::tick()
{
    tickCounter++;
    handleWindowCollision(this);
    handleMovement();
    if ( (tickCounter % 150 == 0) && (InstanceCount<Monster>::getInstanceCount() < 30) )
    {
        spawn();
    }
}

void FireSpirit::handleMovement()
{
    if (tickCounter % 2 == 0)
    {
        moveTorwardPlayer();
    }
    else
    {
        moveRandomly();
    }

    animateWalking();
}

void FireSpirit::animateWalking()
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

void FireSpirit::spawn()
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distribution(-100, 100);
    int randomX = distribution(gen);
    int randomY = distribution(gen);
    getEngine()->addGameComponent(FireSpirit::create(this->getLeft() + randomX, this->getBottom() + randomY, 80, 30, 3, getEngine()));
}

void FireSpirit::handleCollision(const Component *other)
{
    if (dynamic_cast<const FrostBite *>(other))
    {
        getEngine()->removeGameComponent(this);
    }

    if (const ImmovableSprite *immSpritePtr = dynamic_cast<const ImmovableSprite *>(other))
    {
        handleObstacleCollision(this, immSpritePtr);
    }

    if (dynamic_cast<const Player *>(other))
    {
        int smallCenterX = getLeft() + getWidth() / 2;
        int smallCenterY = getTop() + getHeight() / 2;

        int explosionX = smallCenterX - (150 / 2);
        int explosionY = smallCenterY - (150 / 2);
        Explosion::getInstance(explosionX, explosionY, 150, 150, 4, getEngine());
        getEngine()->removeGameComponent(this);
    }
}