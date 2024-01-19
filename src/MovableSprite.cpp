#include "MovableSprite.h"
#include "Graphics.h"
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <iostream>

/**
 * Class that handles sprites that are to move across window or have their sizes altered during their life-cycles, appropriate for deriving a Player-class
 */
// Spelmotor-klass
namespace crane
{

    MovableSprite::MovableSprite(int x, int y, int width, int height, int weight, std::string assetPath) : 
                    Component(x, y, width, height, weight)
    {
        spriteTexture = IMG_LoadTexture(graphic.get_ren(), (assetPath).c_str());
        assetPathTEMP = assetPath;
    }

    MovableSprite *MovableSprite::getInstance(int x, int y, int width, int height, int weight, std::string assetPath)
    {
        return new MovableSprite(x, y, width, height, weight, assetPath);
    }

    void MovableSprite::draw() const
    {
        SDL_RenderCopy(graphic.get_ren(), spriteTexture, NULL, &getRect());
    }

    void MovableSprite::tick() {}

    void MovableSprite::handleCollision(const Component *other) {}

    void MovableSprite::keyDown(const SDL_Event &eve)
    {
        switch (eve.key.keysym.sym)
        {
        case SDLK_UP:
            handleUpArrowKeyDownPress();
            break;
        case SDLK_DOWN:
            handleDownArrowKeyDownPress();
            break;
        case SDLK_LEFT:
            handleLeftArrowKeyDownPress();
            break;
        case SDLK_RIGHT:
            handleRightArrowKeyDownPress();
            break;
        case SDLK_w:
            handleWKeyDownPress();
            break;
        case SDLK_a:
            handleAKeyDownPress();
            break;
        case SDLK_s:
            handleSKeyDownPress();
            break;
        case SDLK_d:
            handleDKeyDownPress();
            break;
        case SDLK_SPACE:
            handleSpaceKeyDownPress();
            break;
        case SDLK_1:
            handleOneKeyDownPress();
            break;
        case SDLK_2:
            handleTwoKeyDownPress();
            break;
        case SDLK_3:
            handleThreeKeyDownPress();
            break;
        }    
    }

    void MovableSprite::keyUp(const SDL_Event &eve)
    {
        switch (eve.key.keysym.sym)
        {
        case SDLK_w:
            handleWKeyRelease();
            break;
        case SDLK_a:
            handleAKeyRelease();
            break;
        case SDLK_s:
            handleSKeyRelease();
            break;
        case SDLK_d:
            handleDKeyRelease();
            break;
        case SDLK_UP:
            handleUpArrowKeyUpRelease();
            break;
        case SDLK_DOWN:
            handleDownArrowKeyUpRelease();
            break;
        case SDLK_LEFT:
            handleLeftArrowKeyUpRelease();
            break;
        case SDLK_RIGHT:
            handleRightArrowKeyUpRelease();
            break;
        }
    }

    /**
     * Getting of speed for which sprite moves in window (speed used for incrementing/decrementing coordinates)
     */
    int MovableSprite::getSpeed() const
    {
        return speed;
    }

    /**
     * Set speed for which sprite moves in window (speed used for incrementing/decrementing coordinates)
     */
    void MovableSprite::setSpeed(int newSpeed)
    {
        speed = newSpeed;
    }

    /**
     * Set a new X position for sprite
     */
    void MovableSprite::setX(int newX)
    {
        rect.x = newX;
        xPosition = newX;
    }

    /**
     * Set a new Y position for sprite
     */
    void MovableSprite::setY(int newY)
    {
        rect.y = newY;
        yPosition = newY;
    }

    /**
     * Set a new texture for sprite, destroying the old one
     */
    void MovableSprite::setTexture(std::string assetPath)
    {
        SDL_DestroyTexture(spriteTexture);
        spriteTexture = IMG_LoadTexture(graphic.get_ren(), (assetPath).c_str());
    }

    MovableSprite::~MovableSprite()
    {
        if (spriteTexture != nullptr)
        {
            SDL_DestroyTexture(spriteTexture);
            spriteTexture = nullptr;
        }
    }

}