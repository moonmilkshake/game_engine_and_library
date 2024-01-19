#ifndef PLAYERELEMENT_H
#define PLAYERELEMENT_H
#include "GameEngine.h"
#include "AttackDirection.h"
#include <string>
#include <vector>

using namespace crane;

class PlayerElement
{
public:
    virtual void performAttack(int throwPower, const AttackDirection direction, int startX, int startY, GameEngine* engine) {}
    virtual void performChargedAttack(int throwPower, const AttackDirection direction, int startX, int startY, GameEngine* engine) {}
    virtual void performSpecialAttack(int throwPower, int startX, int startY, GameEngine* engine) {}
protected:
    PlayerElement() {}
    virtual ~PlayerElement() {}
private:
    PlayerElement(const PlayerElement &) = delete;
    const PlayerElement &operator=(const PlayerElement &) = delete;
};

#endif