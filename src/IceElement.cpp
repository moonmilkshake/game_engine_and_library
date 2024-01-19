#include "IceElement.h"
#include "ThrowableRock.h"
#include "GameEngine.h"
#include "AttackDirection.h"
#include "FrostBite.h"
#include "InstanceCount.h"
#include <string>
#include <vector>

using namespace crane;
using namespace std;

void IceElement::performAttack(int throwPower, const AttackDirection direction, int startX, int startY, GameEngine *engine)
{
    if (InstanceCount<FrostBite>::getInstanceCount() < 1)
    {
        int extraDistance = (throwPower > CHARGED_ATTACK_THRESHOLD) ? throwPower * DISTANCE_MULTIPLY_FACTOR : 0;
        int sizeScaler = 1;
        if (specialAttackActive)
        {
            sizeScaler = SIZE_MULTIPLY_FACTOR;
            specialAttackActive = false;
        }
        switch (direction.getDirection())
        {
        case Direction::Up:
            startY -= DISTANCE_FROM_ATTACKER + (BASE_FROST_HEIGHT * sizeScaler) + extraDistance;
            startX -= (BASE_FROST_WIDTH * sizeScaler) / 2;
            break;
        case Direction::Down:
            startY +=  DISTANCE_FROM_ATTACKER + extraDistance;
            startX -= (BASE_FROST_WIDTH * sizeScaler) / 2;
            break;
        case Direction::Left:
            startX -= DISTANCE_FROM_ATTACKER + (BASE_FROST_WIDTH * sizeScaler) + extraDistance;
            startY -= (BASE_FROST_HEIGHT * sizeScaler) / 2;
            break;
        case Direction::Right:
            startX += DISTANCE_FROM_ATTACKER + extraDistance;
            startY -= (BASE_FROST_HEIGHT * sizeScaler) / 2;
            break;
        default:
            startX = startX;
            startY = startY;
        }
        FrostBite::getInstance(startX, startY, BASE_FROST_WIDTH * sizeScaler, BASE_FROST_HEIGHT * sizeScaler, 3, direction, engine);
    }
}

void IceElement::performChargedAttack(int throwPower, const AttackDirection direction, int startX, int startY, GameEngine *engine) {}

void IceElement::performSpecialAttack(int throwPower, int startX, int startY, GameEngine *engine)
{
    specialAttackActive = true;
}
