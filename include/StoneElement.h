#ifndef STONEELEMENT_H
#define STONEELEMENT_H
#include "PlayerElement.h"
#include "GameEngine.h"
#include <string>
#include <vector>

using namespace crane;

class StoneElement : public PlayerElement
{
public:
    static StoneElement* getInstance() { return new StoneElement(); }
    void performAttack(int throwPower, const AttackDirection direction, const int startX, const int startY, GameEngine* engine) override;
    void performChargedAttack(int throwPower, const AttackDirection direction, const int startX, const int startY, GameEngine* engine) override;
    void performSpecialAttack(int throwPower, const int startX, const int startY, GameEngine* engine) override;
protected:
    StoneElement() {}
    ~StoneElement() {}
private:
    const int BASE_ROCK_SIZE = 25;
    const int MAX_ROCK_SIZE = 200;
    const int CHARGED_ATTACK_THRESHOLD = 30;
    bool determineIfRockIsPassthrough(const int throwPower);
    int centerRockToAttacker(int startCoordinate, int throwPower) const;
};



#endif