#include "ThrowableRock.h"
#include "AnimationHandler.h"
#include "Graphics.h"
#include "MovableSprite.h"
#include "GameEngine.h"
#include "Player.h"
#include "AttackDirection.h"
#include <string>
#include <iostream>

// Spel-klass
using namespace crane;
using namespace std;

const string ThrowableRock::FIRST_ASSET_PATH = "images/throwable_rock/throwable_rock_1.png";
const int ThrowableRock::ANIMATION_DELAY = 2;
const int ThrowableRock::ANIMATION_START_COUNT = 0;
const int ThrowableRock::LAST_ASSET_INDEX = 3;
const int ThrowableRock::ASSETS_SIZE = 4;

ThrowableRock::ThrowableRock(int x, int y, int width, int height, int weight, AttackDirection direction, GameEngine *engine, bool passThrough) : 
                MovableSprite(x, y, width, height, weight, (constants::gResPath + FIRST_ASSET_PATH)), 
                engine(engine), direction(direction), passThrough(passThrough),
                animationHandler(ANIMATION_DELAY, ANIMATION_START_COUNT, LAST_ASSET_INDEX)              
{
    animationHandler.addAssets(throwableRockAssetPaths, 1, ASSETS_SIZE, "images/throwable_rock/throwable_rock_");
    engine->addGameComponent(this);
}

ThrowableRock *ThrowableRock::getInstance(int x, int y, int width, int height, int weight, AttackDirection direction, GameEngine *engine, bool passThrough)
{
    return new ThrowableRock(x, y, width, height, weight, direction, engine, passThrough);
}

void ThrowableRock::tick()
{
    updateAsset();
    move();
}

void ThrowableRock::updateAsset()
{
    if (animationHandler.timeForNextAsset())
    {
        setTexture(constants::gResPath + throwableRockAssetPaths.at(animationHandler.getAnimationCount()) + ".png");
    }
}

void ThrowableRock::move()
{
    int windowWidth, windowHeight;
    windowHeight = graphic.getScreenHeight();
    windowWidth = graphic.getScreenWidth();

    // Removes rock if it leaves the screen, otherwise moves it forward in determined direction
    if (getLeft() < 0 || getTop() > windowHeight || getTop() < 0 || getLeft() > windowWidth)
    {
        engine->removeGameComponent(this);
    }
    else
    {
        switch (direction.getDirection())
        {
        case Direction::Up:
            setY(getTop() - 10);
            break;
        case Direction::Down:
            setY(getTop() + 10);
            break;
        case Direction::Left:
            setX(getLeft() - 10);
            break;
        case Direction::Right:
            setX(getLeft() + 10);
            break;
        default:
            engine->removeGameComponent(this);
        }
    }
}

/**
 * Rock is set to be removed upon collision with anything other than the Player unless it's passthrough,
 * in which case nothing inside the window stops it
 */
void ThrowableRock::handleCollision(const Component *other)
{
    if (dynamic_cast<const Player *>(other) == nullptr && !passThrough)
    {
        engine->removeGameComponent(this);
    }
}
