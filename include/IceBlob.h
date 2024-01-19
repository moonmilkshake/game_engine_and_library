#ifndef ICEBLOB_H
#define ICEBLOB_H
#include "Monster.h"
#include "AnimationHandler.h"
#include <vector>
#include <string>

class IceBlob : public Monster
{
public:
    static IceBlob* create(int x, int y, int width, int height, int weight, GameEngine *engine);
    virtual ~IceBlob() override {}
    void tick() override;
    void handleCollision(const Component *other) override;

protected:
    IceBlob(int x, int y, int width, int height, int weight, GameEngine *engine);

private:
    const static std::string FIRST_ASSET_PATH;
    static const int ANIMATION_DELAY;
    static const int ANIMATION_START_COUNT;
    static const int LAST_ASSET_INDEX;
    static const int ASSETS_SIZE;
    static const int DEFAULT_SPEED;
    std::vector<std::string> walkingRightAssetPaths;
    std::vector<std::string> walkingLeftAssetPaths;
    int tickCounter = 0;
    void handleMovement() override;
    void animateWalking();
    void spawn();
    AnimationHandler rightWalkAnimationHandler;
    AnimationHandler leftWalkAnimationHandler;
};

#endif