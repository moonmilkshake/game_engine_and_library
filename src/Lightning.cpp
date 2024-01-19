#include "Lightning.h"
#include "Graphics.h"
#include "MovableSprite.h"
#include "GameEngine.h"
#include "Player.h"
#include "AnimationHandler.h"
#include "AttackDirection.h"
#include "Constants.h"
#include <string>
#include <iostream>

using namespace crane;
using namespace std;

const string Lightning::FIRST_ASSET_PATH = "images/special_ready/special_ready_1.png";
const int Lightning::ANIMATION_DELAY = 2;
const int Lightning::ANIMATION_START_COUNT = 0;
const int Lightning::LAST_ASSET_INDEX = 7;
const int Lightning::ASSETS_SIZE = 8;

Lightning::Lightning(int x, int y, int width, int height, int weight, GameEngine *engine) : 
            MovableSprite(x, y, width, height, weight, (constants::gResPath + FIRST_ASSET_PATH)), engine(engine),
            animationHandler(ANIMATION_DELAY, ANIMATION_START_COUNT, LAST_ASSET_INDEX, 1)
{
    animationHandler.addAssets(lightningAssetPaths, 1, ASSETS_SIZE, "images/special_ready/special_ready_");
    engine->addGameComponent(this);
}

Lightning *Lightning::getInstance(int x, int y, int width, int height, int weight, GameEngine *engine)
{
    return new Lightning(x, y, width, height, weight, engine);
}

void Lightning::tick()
{
    updateAsset();
}

void Lightning::updateAsset()
{
    if (animationHandler.timeForRemoval())
    {
        engine->removeGameComponent(this);
    }
    else if (animationHandler.timeForNextAsset())
    {
        setTexture(constants::gResPath + lightningAssetPaths.at(animationHandler.getAnimationCount()) + ".png");
    }
}
