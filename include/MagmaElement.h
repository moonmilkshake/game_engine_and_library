#ifndef MAGMAELEMENT_H
#define MAGMAELEMENT_H
#include "PlayerElement.h"
#include "GameEngine.h"
#include <string>
#include <vector>

using namespace crane;

class MagmaElement : public PlayerElement
{
public:
    static MagmaElement* getInstance() { return new MagmaElement(); }
    void performAttack(int throwPower, const AttackDirection direction, int startX, int startY, GameEngine* engine) override;
    void performChargedAttack(int throwPower, const AttackDirection direction, int startX, int startY, GameEngine* engine) override;
    void performSpecialAttack(int throwPower, int startX, int startY, GameEngine* engine) override;
protected:
    MagmaElement() {}
    ~MagmaElement() {}
private:
    const int BASE_FLAME_WIDTH = 80;
    const int BASE_FLAME_HEIGHT = 180;
    const int DISTANCE_FROM_ATTACKER = 100;
    const int CHARGED_ATTACK_THRESHOLD = 30;
    const int SIZE_MULTIPLY_FACTOR = 2;
    const int SPECIAL_DURATION = 4;
};



#endif