#include "StoneElement.h"
#include "ThrowableRock.h"
#include "GameEngine.h"
#include "AttackDirection.h"
#include <string>
#include <vector>

using namespace crane;
using namespace std;

void StoneElement::performAttack(int throwPower, const AttackDirection direction, int startX, int startY, GameEngine* engine)
{
    startX = centerRockToAttacker(startX, throwPower);
    startY = centerRockToAttacker(startY, throwPower);
    if (determineIfRockIsPassthrough(throwPower))
    {
        performChargedAttack(throwPower, direction, startX, startY, engine);
    } 
    else
    {
        ThrowableRock::getInstance(startX, startY, BASE_ROCK_SIZE, BASE_ROCK_SIZE, 3, direction, engine, false);
    }
}

void StoneElement::performChargedAttack(int throwPower, const AttackDirection direction, int startX, int startY, GameEngine* engine)
{
    int rockSize = (throwPower > MAX_ROCK_SIZE) ? MAX_ROCK_SIZE : throwPower;
    ThrowableRock::getInstance(startX, startY, rockSize, rockSize, 3, direction, engine, true);
}

void StoneElement::performSpecialAttack(int throwPower, int startX, int startY, GameEngine* engine)
{
    int rockSize = throwPower * 2;
    ThrowableRock::getInstance(startX, startY, rockSize, rockSize, 3, AttackDirection(Direction::Up), engine, true);
    ThrowableRock::getInstance(startX, startY, rockSize, rockSize, 3, AttackDirection(Direction::Down), engine, true);
    ThrowableRock::getInstance(startX, startY, rockSize, rockSize, 3, AttackDirection(Direction::Right), engine, true);
    ThrowableRock::getInstance(startX, startY, rockSize, rockSize, 3, AttackDirection(Direction::Left), engine, true);
}

int StoneElement::centerRockToAttacker(int startCoordinate, int throwPower) const
{
    return startCoordinate - (throwPower / 2);
}

bool StoneElement::determineIfRockIsPassthrough(const int throwPower)
{
    if (throwPower > CHARGED_ATTACK_THRESHOLD)
    {
        return true;
    }
    else
    {
        return false;
    }
}