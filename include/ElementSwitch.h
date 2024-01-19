#ifndef ELEMENTSWITCH_H
#define ELEMENTSWITCH_H
#include "MovableSprite.h"
#include "AnimationHandler.h"
#include "GameEngine.h"
#include <string>

using namespace crane;

class ElementSwitch : public MovableSprite
{
public:
    static ElementSwitch* getInstance(int x, int y, int width, int height, int weight, GameEngine *engine);
    void tick() override;

protected:
    ElementSwitch(int x, int y, int width, int height, int weight, std::string assetPath, GameEngine *engine);

private:
    static const std::string FIRST_ASSET_PATH; 
    const static int ANIMATION_DELAY;
    const static int ANIMATION_START_COUNT;
    const static int LAST_ASSET_INDEX;
    const static int ASSETS_SIZE;
    std::vector<std::string> elementSwitchAssetPaths;
    GameEngine *engine; 
    AnimationHandler animationHandler;
    void updateAssets();
};

#endif