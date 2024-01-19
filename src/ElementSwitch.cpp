#include "ElementSwitch.h"
#include "AnimationHandler.h"
#include "GameEngine.h"
#include "Constants.h"
#include <string>
#include <iostream>

const std::string ElementSwitch::FIRST_ASSET_PATH = "images/golem_element_switch/golem_element_switch_1.png";
const int ElementSwitch::ANIMATION_DELAY = 3;
const int ElementSwitch::ANIMATION_START_COUNT = 0;
const int ElementSwitch::LAST_ASSET_INDEX = 9;
const int ElementSwitch::ASSETS_SIZE = 10;

ElementSwitch::ElementSwitch(int x, int y, int width, int height, int weight, std::string assetPath, GameEngine *engine) : 
                MovableSprite(x, y, width, height, weight, constants::gResPath + assetPath), engine(engine),
                animationHandler(ANIMATION_DELAY, ANIMATION_START_COUNT, LAST_ASSET_INDEX, 1)

{
    animationHandler.addAssets(elementSwitchAssetPaths, 1, ASSETS_SIZE, "images/golem_element_switch/golem_element_switch_");
    engine->addGameComponent(this);
}

ElementSwitch *ElementSwitch::getInstance(int x, int y, int width, int height, int weight, GameEngine *engine)
{

    return new ElementSwitch(x, y, width, height, weight, FIRST_ASSET_PATH, engine);
}

void ElementSwitch::tick()
{
    updateAssets();
}

void ElementSwitch::updateAssets()
{
    if (animationHandler.timeForRemoval())
    {
        engine->removeGameComponent(this);
    }
    else if (animationHandler.timeForNextAsset())
    {
        setTexture(constants::gResPath + elementSwitchAssetPaths.at(animationHandler.getAnimationCount()) + ".png");
        //std::cout << constants::gResPath + elementSwitchAssetPaths.at(animationHandler.getAnimationCount()) + ".png" << std::endl;
    }
}