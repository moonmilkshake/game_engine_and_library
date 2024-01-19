#ifndef FROSTBITE_H
#define FROSTBITE_H
#include "MovableSprite.h"
#include "InstanceCount.h"
#include "AnimationHandler.h"
#include "GameEngine.h"
#include "Constants.h"
#include "AttackDirection.h"
#include <vector>
#include <string>

using namespace crane;

    class FrostBite : public MovableSprite, public InstanceCount<FrostBite>
    {
    public:
        static FrostBite *getInstance(int x, int y, int width, int height, int weight, AttackDirection direction, GameEngine* engine);
        virtual ~FrostBite() override {}
        void tick() override;
        void handleCollision(const Component* other) override;
    protected:
        FrostBite(int x, int y, int width, int height, int weight, AttackDirection direction, GameEngine* engine);
    private:
        const static std::string FIRST_ASSET_PATH;
        const static int LAST_ASSET_INDEX;
        const static int ANIMATION_DELAY;
        const static int ANIMATION_START_COUNT;
        const static int ASSETS_SIZE;
        std::vector<std::string> frostBiteAssetPaths;
        GameEngine* engine;
        AttackDirection direction;
        AnimationHandler animationHandler;
        void updateAsset();
    };

#endif