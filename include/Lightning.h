#ifndef LIGHTNING_H
#define LIGHTNING_H
#include "MovableSprite.h"
#include "AnimationHandler.h"
#include "GameEngine.h"
#include <string>
#include <vector>

using namespace crane;

class Lightning : public MovableSprite
{
public:
    static Lightning* getInstance(int x, int y, int width, int height, int weight, GameEngine *engine);
    virtual ~Lightning() override {}
    void tick() override;

protected:
    Lightning(int x, int y, int width, int height, int weight, GameEngine *engine);

private:
    const static std::string FIRST_ASSET_PATH;
    const static int LAST_ASSET_INDEX;
    const static int ANIMATION_DELAY;
    const static int ANIMATION_START_COUNT;
    const static int ASSETS_SIZE;
    std::vector<std::string> lightningAssetPaths;
    GameEngine *engine;
    AnimationHandler animationHandler;
    void updateAsset();
};

#endif