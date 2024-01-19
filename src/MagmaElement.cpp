#include "MagmaElement.h"
#include "ThrowableRock.h"
#include "GameEngine.h"
#include "AttackDirection.h"
#include "FlameBlast.h"
#include "InstanceCount.h"
#include <string>
#include <vector>

using namespace crane;
using namespace std;

void MagmaElement::performAttack(int throwPower, const AttackDirection direction, int startX, int startY, GameEngine *engine)
{
    if (InstanceCount<FlameBlast>::getInstanceCount() < 2)
    {
        switch (direction.getDirection())
        {
        case Direction::Up:
            startY -= DISTANCE_FROM_ATTACKER + BASE_FLAME_HEIGHT;
            startX -= BASE_FLAME_WIDTH / 2;
            break;
        case Direction::Down:
            startY +=  DISTANCE_FROM_ATTACKER;
            startX -= BASE_FLAME_WIDTH / 2;
            break;
        case Direction::Left:
            startX -= DISTANCE_FROM_ATTACKER + BASE_FLAME_WIDTH;
            startY -= (BASE_FLAME_HEIGHT / 1.5);
            break;
        case Direction::Right:
            startX += DISTANCE_FROM_ATTACKER;
            startY -= (BASE_FLAME_HEIGHT / 1.5);
            break;
        default:
            startX = startX;
            startY = startY;
        }
        if (throwPower > CHARGED_ATTACK_THRESHOLD)
        {
            performChargedAttack(throwPower, direction, startX, startY, engine);
        }
        else
        {
            int prolongDuration = 0;
            FlameBlast::getInstance(startX, startY, BASE_FLAME_WIDTH, BASE_FLAME_HEIGHT, 3, direction, engine, prolongDuration);
        }
    }
}

void MagmaElement::performChargedAttack(int throwPower, const AttackDirection direction, int startX, int startY, GameEngine *engine)
{
    int prolongDuration = throwPower / 10;
    FlameBlast::getInstance(startX, startY, BASE_FLAME_WIDTH, BASE_FLAME_HEIGHT, 3, direction, engine, prolongDuration);
}

void MagmaElement::performSpecialAttack(int throwPower, int startX, int startY, GameEngine *engine)
{
    int width = BASE_FLAME_WIDTH * SIZE_MULTIPLY_FACTOR;
    int height = BASE_FLAME_HEIGHT * SIZE_MULTIPLY_FACTOR;
    startX -= width / 2;
    startY -= height / 1.5;
    FlameBlast::getInstance(startX, startY, width, height, 3, AttackDirection(Direction::Center), engine, SPECIAL_DURATION);
}
