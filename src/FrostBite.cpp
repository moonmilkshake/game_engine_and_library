#include "FrostBite.h"
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

const string FrostBite::FIRST_ASSET_PATH = "images/frost_bite/frost_bite_1.png";
const int FrostBite::ANIMATION_DELAY = 2;
const int FrostBite::ANIMATION_START_COUNT = 0;
const int FrostBite::LAST_ASSET_INDEX = 21;
const int FrostBite::ASSETS_SIZE = 22;

FrostBite::FrostBite(int x, int y, int width, int height, int weight, AttackDirection direction, GameEngine *engine) : 
            MovableSprite(x, y, width, height, weight, (constants::gResPath + FIRST_ASSET_PATH)), engine(engine), direction(direction),
            animationHandler(ANIMATION_DELAY, ANIMATION_START_COUNT, LAST_ASSET_INDEX, 1)
{
    animationHandler.addAssets(frostBiteAssetPaths, 1, ASSETS_SIZE, "images/frost_bite/frost_bite_");
    engine->addGameComponent(this);
}

FrostBite *FrostBite::getInstance(int x, int y, int width, int height, int weight, AttackDirection direction, GameEngine *engine)
{
    return new FrostBite(x, y, width, height, weight, direction, engine);
}

void FrostBite::tick()
{
    updateAsset();
}

void FrostBite::updateAsset()
{
    if (animationHandler.timeForRemoval())
    {
        engine->removeGameComponent(this);
    }
    else if (animationHandler.timeForNextAsset())
    {
        setTexture(constants::gResPath + frostBiteAssetPaths.at(animationHandler.getAnimationCount()) + ".png");
    }
}

void FrostBite::handleCollision(const Component *other)
{

}
