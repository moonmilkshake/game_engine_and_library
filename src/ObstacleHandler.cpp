#include "ObstacleHandler.h"
#include "MovableSprite.h"
#include "ImmovableSprite.h"
#include "Graphics.h"
#include <iostream>

/**
 * Class that handles collision between MovableSprites and ImmovableSprites/Window
 */
// Spelmotor-klass
namespace crane
{
    /**
     * Handle collision between MovableSprite and ImmovableSprite
     */
    void ObstacleHandler::handleObstacleCollision(MovableSprite *movSprite, const ImmovableSprite *immSprite)
    {
        {
            int speed = movSprite->getSpeed();

            int left = movSprite->getLeft();
            int right = movSprite->getRight();
            int top = movSprite->getTop();
            int bottom = movSprite->getBottom();

            int otherLeft = immSprite->getLeft();
            int otherRight = immSprite->getRight();
            int otherTop = immSprite->getTop();
            int otherBottom = immSprite->getBottom();

            // Stop movSprite from walking through immSprite in direction ->
            if (top < otherBottom)
            {
                if (bottom > otherTop)
                {
                    if (right > otherLeft && right <= otherLeft + speed)
                    {
                        if (left < otherLeft)
                        {
                            movSprite->setX(otherLeft - movSprite->getWidth());
                        }
                    }
                }
            }
            // Stop movSprite from walking through immSprite in direction <-
            if (top < otherBottom)
            {
                if (bottom > otherTop)
                {
                    if (left < otherRight && left >= otherRight - speed)
                    {
                        if (right > otherRight)
                        {
                            movSprite->setX(otherRight);
                        }
                    }
                }
            }
            // Stop movSprite from walking through immSprite in direction ^
            if (left < otherRight)
            {
                if (right > otherLeft)
                {
                    if (top < otherBottom && top >= otherBottom - speed)
                    {
                        if (bottom > otherBottom)
                        {
                            movSprite->setY(otherBottom);
                        }
                    }
                }
            }
            // Stop movSprite from walking through immSprite in direction v
            if (left < otherRight)
            {
                if (right > otherLeft)
                {
                    if (bottom > otherTop && bottom <= otherTop + speed)
                    {
                        if (top < otherTop)
                        {
                            movSprite->setY(otherTop - movSprite->getHeight());
                        }
                    }
                }
            }
        }
    }

    /**
     * Handle collision between MovableSprite and Window
     */
    void ObstacleHandler::handleWindowCollision(MovableSprite *movSprite)
    {
        int windowWidth, windowHeight;
        windowWidth = graphic.getScreenWidth();
        windowHeight = graphic.getScreenHeight();
        if (movSprite->getLeft() < 0)
        {
            movSprite->setX(windowWidth - movSprite->getWidth());
        }
        if (movSprite->getTop() < 0)
        {
            movSprite->setY(windowHeight - movSprite->getHeight());
        }
        if (movSprite->getRight() > windowWidth)
        {
            movSprite->setX(0);
        }
        if (movSprite->getBottom() > windowHeight)
        {
            movSprite->setY(0);
        }
    }

}