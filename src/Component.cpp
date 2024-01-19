#include "Component.h"

// Spelmotor-klass
namespace crane
{

    Component::Component(int x, int y, int width, int height, int weight) : rect{x, y, width, height}, weight(weight) {}

    Component::~Component() {}

    bool Component::checkCollision(const Component *other) const
    {
        return SDL_HasIntersection(&getRect(), &other->getRect());
    }

    int Component::getLeft() const
    {
        return rect.x;
    }
    int Component::getTop() const
    {
        return rect.y;
    }
    int Component::getRight() const
    {
        return rect.x + rect.w;
    }
    int Component::getBottom() const
    {
        return rect.y + rect.h;
    }

    int Component::getWidth() const
    {
        return rect.w;
    }

    int Component::getHeight() const
    {
        return rect.h;
    }

    int Component::getWeight() const
    {
        return weight;
    }
    
}