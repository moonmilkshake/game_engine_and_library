#ifndef ICEELEMENT_H
#define ICEELEMENT_H
#include "PlayerElement.h"
#include "GameEngine.h"
#include <string>
#include <vector>

using namespace crane;

class IceElement : public PlayerElement
{
public:
    static IceElement* getInstance() { return new IceElement(); }
    void performAttack(int throwPower, const AttackDirection direction, int startX, int startY, GameEngine* engine) override;
    void performChargedAttack(int throwPower, const AttackDirection direction, int startX, int startY, GameEngine* engine) override;
    void performSpecialAttack(int throwPower, int startX, int startY, GameEngine* engine) override;
protected:
    IceElement() {}
    ~IceElement() {}
private:
    const int BASE_FROST_WIDTH = 150;
    const int BASE_FROST_HEIGHT = 90;
    const int DISTANCE_FROM_ATTACKER = 40;
    const int CHARGED_ATTACK_THRESHOLD = 30;
    const int DISTANCE_MULTIPLY_FACTOR = 5;
    const int SIZE_MULTIPLY_FACTOR = 3;
    bool specialAttackActive = false;
};

#endif