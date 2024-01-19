#include "Button.h"
#include <SDL2/SDL_ttf.h>
#include "Graphics.h"
#include <SDL2/SDL_image.h>
#include "Component.h"
#include "Constants.h"
#include <iostream>

// Spelmotor-klass
namespace crane
{

    Button::Button(int x, int y, int width, int height, int weight, std::string upAssetPath, std::string downAssetPath) : 
            Component(x, y, width, height, weight), isDown(false), upIcon(nullptr), downIcon(nullptr)
    {
        upIcon = IMG_LoadTexture(graphic.get_ren(), upAssetPath.c_str());
        if (!upIcon)
        {
            std::cerr << "Failed to load texture: " << upAssetPath << " SDL_image Error: " << IMG_GetError() << std::endl;
        }
        downIcon = IMG_LoadTexture(graphic.get_ren(), downAssetPath.c_str());
        if (!downIcon)
        {
            std::cerr << "Failed to load texture: " << downAssetPath << " SDL_image Error: " << IMG_GetError() << std::endl;
        }
    }

    Button::~Button()
    {
        SDL_DestroyTexture(upIcon);
        SDL_DestroyTexture(downIcon);
        upIcon = nullptr;
        downIcon = nullptr;
    }

    void Button::mouseDown(const SDL_Event &event)
    {
        SDL_Point p = {event.button.x, event.button.y};
        if (SDL_PointInRect(&p, &getRect()))
        {
            isDown = true;
        }
    }

    void Button::mouseUp(const SDL_Event &event)
    {
        SDL_Point p = {event.button.x, event.button.y};
        if (SDL_PointInRect(&p, &getRect()))
        {
            perform(this);
            isDown = false;
        }
    }

    void Button::draw() const
    {
        SDL_Texture *icon = isDown && downIcon ? downIcon : upIcon;
        if (icon != nullptr)
        {
            SDL_RenderCopy(graphic.get_ren(), icon, NULL, &getRect());
        }
    }
}
