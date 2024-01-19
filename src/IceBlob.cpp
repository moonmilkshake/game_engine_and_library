#include "IceBlob.h"
#include "Monster.h"
#include "Constants.h"
#include "FlameBlast.h"
#include <string>
#include <vector>
#include <random>

using namespace std;

const string IceBlob::FIRST_ASSET_PATH = "images/iceblob_rightwalk/ice_blob_walk_right_1";
const int IceBlob::ANIMATION_DELAY = 2;
const int IceBlob::ANIMATION_START_COUNT = 0;
const int IceBlob::LAST_ASSET_INDEX = 5;
const int IceBlob::ASSETS_SIZE = 6;
const int IceBlob::DEFAULT_SPEED = 1;

IceBlob::IceBlob(int x, int y, int width, int height, int weight, GameEngine* engine) : 
            Monster(x, y, width, height, weight, DEFAULT_SPEED, constants::gResPath + FIRST_ASSET_PATH, engine),
            rightWalkAnimationHandler(ANIMATION_DELAY, ANIMATION_START_COUNT, LAST_ASSET_INDEX),
            leftWalkAnimationHandler(ANIMATION_DELAY, ANIMATION_START_COUNT, LAST_ASSET_INDEX) 
{
    rightWalkAnimationHandler.addAssets(walkingRightAssetPaths, 1, ASSETS_SIZE, "images/ice_blob_rightwalk/ice_blob_walk_right_");
    leftWalkAnimationHandler.addAssets(walkingLeftAssetPaths, 1, ASSETS_SIZE, "images/ice_blob_leftwalk/ice_blob_walk_left_");
}

IceBlob* IceBlob::create(int x, int y, int width, int height, int weight, GameEngine *engine)
{
    return new IceBlob(x, y, width, height, weight, engine);
}

void IceBlob::tick()
{
    tickCounter++;
    handleWindowCollision(this);
    handleMovement();
    if ( (tickCounter % 300 == 0) && (InstanceCount<Monster>::getInstanceCount() < 30) )
    {
        spawn();
    }
}

void IceBlob::spawn()
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distribution(-100, 100);
    int randomX = distribution(gen);
    int randomY = distribution(gen);
    getEngine()->addGameComponent(IceBlob::create(this->getLeft() + randomX, this->getBottom() + randomY, 45, 30, 3, getEngine()));
}

void IceBlob::handleMovement()
{
    moveTorwardPlayer();
    animateWalking();
}

void IceBlob::animateWalking()
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

void IceBlob::handleCollision(const Component *other)
{
    if (dynamic_cast<const FlameBlast *>(other))
    {
        getEngine()->removeGameComponent(this);
    }

    if (const ImmovableSprite *immSpritePtr = dynamic_cast<const ImmovableSprite *>(other))
    {
        handleObstacleCollision(this, immSpritePtr);
    }

    if (dynamic_cast<const Player *>(other))
    {
        if (getXVelocity() > 0)
        {
            setX(getLeft() - 150);
        }
        else
        {
            setX(getLeft() + 150);
        }
    }
}