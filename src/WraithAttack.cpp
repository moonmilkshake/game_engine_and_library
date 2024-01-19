#include "WraithAttack.h"
#include "AnimationHandler.h"
#include "MovableSprite.h"
#include "GameEngine.h"
#include "Constants.h"
#include "Player.h"
#include <string>
#include <vector>

using namespace crane;
using namespace std;

const string WraithAttack::FIRST_ASSET_PATH = "images/wraith_attack/wraith_attack_1.png";
const int WraithAttack::ANIMATION_DELAY = 3;
const int WraithAttack::ANIMATION_START_COUNT = 0;
const int WraithAttack::LAST_ASSET_INDEX = 9;
const int WraithAttack::ASSETS_SIZE = 10;

WraithAttack::WraithAttack(int x, int y, int width, int height, int weight, GameEngine *engine) : 
            MovableSprite(x, y, width, height, weight, constants::gResPath + FIRST_ASSET_PATH), engine(engine),
            animationHandler(ANIMATION_DELAY, ANIMATION_START_COUNT, LAST_ASSET_INDEX, 1)
{
    animationHandler.addAssets(wraithAttackAssetPaths, 1, ASSETS_SIZE, "images/wraith_attack/wraith_attack_");
    engine->addGameComponent(this);
}

WraithAttack* WraithAttack::create(int x, int y, int width, int height, int weight, GameEngine *engine)
{
    return new WraithAttack(x, y, width, height, weight, engine);
}

void WraithAttack::tick()
{
    updateAsset();
}

void WraithAttack::updateAsset()
{
    if (animationHandler.timeForRemoval())
    {
        engine->removeGameComponent(this);
    }
    else if (animationHandler.timeForNextAsset())
    {
        setTexture(constants::gResPath + wraithAttackAssetPaths.at(animationHandler.getAnimationCount()) + ".png");
    }
}

void WraithAttack::handleCollision(const Component *other)
{
    if (dynamic_cast<const Player *>(other))
    {
        damageDealt = true;
    }
}
