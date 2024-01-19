#ifndef WRAITHATTACK_H
#define WRAITHATTACK_H
#include "MovableSprite.h"
#include "AnimationHandler.h"
#include "GameEngine.h"

using namespace crane;
class WraithAttack : public MovableSprite
{
public:
    static WraithAttack *create(int x, int y, int width, int height, int weight, GameEngine *engine);
    void tick() override;
    void handleCollision(const Component *other) override;
    bool getDamageDealt() const { return damageDealt; }

protected:
    WraithAttack(int x, int y, int width, int height, int weight, GameEngine *engine);

private:
    const static std::string FIRST_ASSET_PATH;
    const static int ANIMATION_DELAY;
    const static int ANIMATION_START_COUNT;
    const static int LAST_ASSET_INDEX;
    const static int ASSETS_SIZE;
    std::vector<std::string> wraithAttackAssetPaths;
    GameEngine* engine;
    AnimationHandler animationHandler;
    void updateAsset();
    bool damageDealt = false;
};

#endif