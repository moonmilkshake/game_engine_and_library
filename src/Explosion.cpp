#include "Explosion.h"
#include "AnimationHandler.h"
#include "MovableSprite.h"
#include "GameEngine.h"
#include "Constants.h"
#include <string>
#include <vector>

using namespace crane;
using namespace std;

const string Explosion::FIRST_ASSET_PATH = "images/explosion/Explosion_1.png";
const int Explosion::ANIMATION_DELAY = 3;
const int Explosion::ANIMATION_START_COUNT = 0;
const int Explosion::LAST_ASSET_INDEX = 9;
const int Explosion::ASSETS_SIZE = 10;

Explosion::Explosion(int x, int y, int width, int height, int weight, GameEngine *engine) : 
            MovableSprite(x, y, width, height, weight, constants::gResPath + FIRST_ASSET_PATH), engine(engine),
            animationHandler(ANIMATION_DELAY, ANIMATION_START_COUNT, LAST_ASSET_INDEX, 1)
{
    animationHandler.addAssets(explosionAssetPaths, 1, ASSETS_SIZE, "images/explosion/Explosion_");
    engine->addGameComponent(this);
}

Explosion* Explosion::getInstance(int x, int y, int width, int height, int weight, GameEngine *engine)
{
    return new Explosion(x, y, width, height, weight, engine);
}

void Explosion::tick()
{
    updateAsset();
}

void Explosion::updateAsset()
{
    if (animationHandler.timeForRemoval())
    {
        engine->removeGameComponent(this);
    }
    else if (animationHandler.timeForNextAsset())
    {
        setTexture(constants::gResPath + explosionAssetPaths.at(animationHandler.getAnimationCount()) + ".png");
    }
}
