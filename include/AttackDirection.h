#ifndef ATTACKDIRECTION_H
#define ATTACKDIRECTION_H

enum class Direction {
    Up,
    Down,
    Left,
    Right,
    Center
};

class AttackDirection
{
public:
    AttackDirection() {}
    AttackDirection(Direction dir) : direction(dir) {}
    const Direction getDirection() const { return direction; }
private:
    Direction direction;
};

#endif