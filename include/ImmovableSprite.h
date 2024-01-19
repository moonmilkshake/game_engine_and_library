#ifndef IMMOVABLESPRITE_H
#define IMMOVABLESPRITE_H
#include "Component.h"
#include <string>

// Spelmotor-klass
namespace crane
{

    class ImmovableSprite : public Component
    {
    public:
        static ImmovableSprite *getInstance(int x, int y, int width, int height, int weight, std::string assetPath);
        virtual ~ImmovableSprite() override;
        void handleCollision(const Component *other) override;

    protected:
        ImmovableSprite(int x, int y, int width, int height, int weight, std::string assetPath);
        void draw() const override;
        void tick() override;

    private:
        SDL_Texture *spriteTexture;
        ImmovableSprite(const ImmovableSprite &) = delete;
        ImmovableSprite &operator=(const ImmovableSprite &) = delete;
    };

}

#endif