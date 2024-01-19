#include "FlameBlast.h"
#include "AnimationHandler.h"
#include "Graphics.h"
#include "MovableSprite.h"
#include "GameEngine.h"
#include "Player.h"
#include "AttackDirection.h"
#include <string>
#include <iostream>

using namespace crane;
using namespace std;

const string FlameBlast::FIRST_ASSET_PATH = "images/flame_blast/flame_blast_1.png";
const int FlameBlast::ANIMATION_DELAY = 2;
const int FlameBlast::ANIMATION_START_COUNT = 0;
const int FlameBlast::LAST_ASSET_INDEX = 5;
const int FlameBlast::ASSETS_SIZE = 6;

FlameBlast::FlameBlast(int x, int y, int width, int height, int weight, AttackDirection direction, GameEngine *engine, int duration) : 
            MovableSprite(x, y, width, height, weight, (constants::gResPath + FIRST_ASSET_PATH)),
            engine(engine),
            direction(direction),
            animationHandler((ANIMATION_DELAY), ANIMATION_START_COUNT, LAST_ASSET_INDEX, 4 + duration)
{
    animationHandler.addAssets(flameBlastAssetPaths, 1, ASSETS_SIZE, "images/flame_blast/flame_blast_");
    engine->addGameComponent(this);
}

FlameBlast *FlameBlast::getInstance(int x, int y, int width, int height, int weight, AttackDirection direction, GameEngine *engine, int duration)
{
    return new FlameBlast(x, y, width, height, weight, direction, engine, duration);
}

void FlameBlast::tick()
{
    updateAsset();
}

void FlameBlast::updateAsset()
{
    if (animationHandler.timeForRemoval())
    {
        engine->removeGameComponent(this);
    }
    else if (animationHandler.timeForNextAsset())
    {
        setTexture(constants::gResPath + flameBlastAssetPaths.at(animationHandler.getAnimationCount()) + ".png");
    }
}

void FlameBlast::handleCollision(const Component *other)
{

}
