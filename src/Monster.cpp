#include "Monster.h"
#include "MovableSprite.h"
#include "Player.h"
#include "Constants.h"
#include "Explosion.h"
#include "ThrowableRock.h"
#include "GameEngine.h"
#include <random>
#include <string>
#include <iostream>

using namespace crane;
using namespace std;

Monster::Monster(int x, int y, int width, int height, int weight, int speed, string assetPath, GameEngine *engine) : 
            MovableSprite(x, y, width, height, weight, assetPath), engine(engine)
{
    this->setSpeed(speed);
}

/**
 * Method for moving monster torward player
 */
void Monster::moveTorwardPlayer()
{
    Player* player = Player::getInstance();
    if (player)
    {
        int playerX = player->getPlayerXCenter();
        int playerY = player->getPlayerYCenter();
        if (getLeft() > playerX)
        {
            setX(getLeft() - getSpeed());
            xVelocity = -getSpeed();
        }
        if (getLeft() < playerX)
        {
            setX(getLeft() + getSpeed());
            xVelocity = getSpeed();
        }
        if (getTop() > playerY)
        {
            setY(getTop() - getSpeed());
        }
        if (getTop() < playerY)
        {
            setY(getTop() + getSpeed());
        }
    }
}

void Monster::moveRandomly()
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distribution(-getSpeed()*3, getSpeed()*3);
    int randomXMovement = distribution(gen);
    int randomYMovement = distribution(gen);
    this->setX(this->getLeft() + randomXMovement);
    this->setY(this->getTop() + randomYMovement);
    xVelocity = randomXMovement;
}
