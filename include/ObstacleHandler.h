#ifndef OBSTACLEHANDLER_H
#define OBSTACLEHANDLER_H
#include "MovableSprite.h"
#include "ImmovableSprite.h"

// Spelmotor-klass
namespace crane
{

    class ObstacleHandler
    {
    public:
        ObstacleHandler() = default;

    protected:
        void handleObstacleCollision(MovableSprite *movSprite, const ImmovableSprite *immSprite);
        void handleWindowCollision(MovableSprite *movSprite);

    private:
        int left;
        int right;
        int top;
        int bottom;
        int otherLeft;
        int otherRight;
        int otherTop;
        int otherBottom;
        ObstacleHandler(const ObstacleHandler &) = delete;
        ObstacleHandler &operator=(const ObstacleHandler &) = delete;
    };

}

#endif