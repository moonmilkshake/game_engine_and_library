#ifndef WRAITH_H
#define WRAITH_H
#include "Monster.h"
#include "AnimationHandler.h"
#include <vector>
#include <string>

class Wraith : public Monster
{
public:
    static Wraith* create(int x, int y, int width, int height, int weight, GameEngine *engine);
    virtual ~Wraith() override {}
    void tick() override;
    void handleCollision(const Component *other) override;

protected:
    Wraith(int x, int y, int width, int height, int weight, GameEngine *engine);

private:
    const static std::string FIRST_ASSET_PATH;
    static const int WALK_ANIMATION_DELAY;
    static const int ATTACK_ANIMATION_DELAY;
    static const int ANIMATION_START_COUNT;
    static const int LAST_ASSET_INDEX;
    static const int ASSETS_SIZE;
    static const int DEFAULT_SPEED;
    static const int START_LIFE = 5;
    std::vector<std::string> walkingRightAssetPaths;
    std::vector<std::string> walkingLeftAssetPaths;
    std::vector<std::string> attackRightAssetPaths;
    std::vector<std::string> attackLeftAssetPaths;
    int tickCounter = 0;
    void handleMovement() override;
    void animateWalking();
    void animateAttack();
    bool animatingAttack = false;
    void spawn();
    AnimationHandler rightWalkAnimationHandler;
    AnimationHandler leftWalkAnimationHandler;
    AnimationHandler attackRightAnimationHandler;
    AnimationHandler attackLeftAnimationHandler;
    int life;
};

#endif