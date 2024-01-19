#ifndef FLAMEBLAST_H
#define FLAMEBLAST_H
#include "MovableSprite.h"
#include "InstanceCount.h"
#include "AnimationHandler.h"
#include "InstanceCount.h"
#include "GameEngine.h"
#include "Constants.h"
#include "AttackDirection.h"
#include <vector>
#include <string>

using namespace crane;

    class FlameBlast : public MovableSprite, public InstanceCount<FlameBlast>
    {
    public:
        static FlameBlast *getInstance(int x, int y, int width, int height, int weight, AttackDirection direction, GameEngine* engine, int duration);
        virtual ~FlameBlast() override {}
        void tick() override;
        void handleCollision(const Component* other) override;
    protected:
        FlameBlast(int x, int y, int width, int height, int weight, AttackDirection direction, GameEngine* engine, int duration);
    private:
        const static std::string FIRST_ASSET_PATH;
        const static int ANIMATION_DELAY;
        const static int ANIMATION_START_COUNT;
        const static int LAST_ASSET_INDEX;
        const static int ASSETS_SIZE;
        std::vector<std::string> flameBlastAssetPaths;
        GameEngine* engine;
        AttackDirection direction;
        AnimationHandler animationHandler;
        void updateAsset();
    };

#endif