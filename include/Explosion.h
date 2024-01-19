#ifndef EXPLOSION_H
#define EXPLOSION_H
#include "MovableSprite.h"
#include "AnimationHandler.h"
#include "GameEngine.h"

//Spel-klass
using namespace crane;
class Explosion : public MovableSprite
{
public:
    static Explosion *getInstance(int x, int y, int width, int height, int weight, GameEngine *engine);
    void tick() override;

protected:
    Explosion(int x, int y, int width, int height, int weight, GameEngine *engine);

private:
    const static std::string FIRST_ASSET_PATH;
    const static int ANIMATION_DELAY;
    const static int ANIMATION_START_COUNT;
    const static int LAST_ASSET_INDEX;
    const static int ASSETS_SIZE;
    std::vector<std::string> explosionAssetPaths;
    GameEngine* engine;
    AnimationHandler animationHandler;
    void updateAsset();
};

#endif