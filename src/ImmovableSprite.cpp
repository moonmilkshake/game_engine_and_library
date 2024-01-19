#include "ImmovableSprite.h"
#include "Graphics.h"
#include <iostream>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

/**
 * Class that handles sprites that are to remain stationary and not have their coordinates or size altered
 */
// Spelmotor-klass
namespace crane
{

    ImmovableSprite::ImmovableSprite(int x, int y, int width, int height, int weight, std::string assetPath) : 
                        Component(x, y, width, height, weight)
    {
        spriteTexture = IMG_LoadTexture(graphic.get_ren(), (assetPath).c_str());
    }

    ImmovableSprite *ImmovableSprite::getInstance(int x, int y, int width, int height, int weight, std::string assetPath)
    {
        return new ImmovableSprite(x, y, width, height, weight, assetPath);
    }

    void ImmovableSprite::draw() const
    {
        SDL_RenderCopy(graphic.get_ren(), spriteTexture, NULL, &getRect());
    }

    void ImmovableSprite::tick() {}

    void ImmovableSprite::handleCollision(const Component *other) {}

    ImmovableSprite::~ImmovableSprite()
    {
        SDL_DestroyTexture(spriteTexture);
        spriteTexture = nullptr;
    }

}