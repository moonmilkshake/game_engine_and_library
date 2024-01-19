#ifndef THROWABLEROCK_H
#define THROWABLEROCK_H
#include "MovableSprite.h"
#include "AnimationHandler.h"
#include "GameEngine.h"
#include "Constants.h"
#include "AttackDirection.h"
#include <vector>
#include <string>

using namespace crane;

    class ThrowableRock : public MovableSprite
    {
    public:
        static ThrowableRock *getInstance(int x, int y, int width, int height, int weight, AttackDirection direction, GameEngine* engine, bool passThrough);
        virtual ~ThrowableRock() override {}
        void tick() override;
        void handleCollision(const Component* other) override;
    protected:
        ThrowableRock(int x, int y, int width, int height, int weight, AttackDirection direction, GameEngine* engine, bool passThrough);
    private:
        const static std::string FIRST_ASSET_PATH;
        const static int LAST_ASSET_INDEX;
        const static int ANIMATION_DELAY;
        const static int ANIMATION_START_COUNT;
        const static int ASSETS_SIZE;        
        std::vector<std::string> throwableRockAssetPaths;
        GameEngine* engine;
        AttackDirection direction;
        bool passThrough;
        AnimationHandler animationHandler;
        void updateAsset();
        void move();
    };

#endif