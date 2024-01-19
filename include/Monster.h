#ifndef MONSTER_H
#define MONSTER_H
#include "Player.h"
#include "MovableSprite.h"
#include "ObstacleHandler.h"
#include "InstanceCount.h"
#include <string>

using namespace crane;

class Monster : public MovableSprite, public ObstacleHandler, public InstanceCount<Monster>
{
public:
    virtual ~Monster() override {}
    void tick() override {}
    void handleCollision(const Component *other) override {}
    int getXVelocity() const { return xVelocity; }

protected:
    Monster(int x, int y, int width, int height, int weight, int speed, std::string assetPath, GameEngine *engine);
    void moveTorwardPlayer();
    void moveRandomly();
    GameEngine* getEngine() const { return engine; }

private:
    GameEngine *engine;
    unsigned int walkingAssetCount = 0;
    int xVelocity;
    virtual void handleMovement() {}
};

#endif