#ifndef MOVABLESPRITE_H
#define MOVABLESPRITE_H
#include "Component.h"
#include <string>

// Spelmotor-klass
namespace crane
{

    class MovableSprite : public Component
    {
    public:
        static MovableSprite *getInstance(int x, int y, int width, int height, int weight, std::string assetPath);
        virtual ~MovableSprite() override;
        void handleCollision(const Component *other) override;
        void setSpeed(int newSpeed);
        int getSpeed() const;
        void keyDown(const SDL_Event &) override;
        void keyUp(const SDL_Event &) override;
        void setX(int newX);
        void setY(int newY);
        void setTexture(std::string assetPath);
    protected:
        MovableSprite(int x, int y, int width, int height, int weight, std::string assetPath);
        std::string assetPathTEMP;
        void draw() const override;
        void tick() override;
        virtual void handleUpArrowKeyDownPress() {}
        virtual void handleDownArrowKeyDownPress() {}
        virtual void handleLeftArrowKeyDownPress() {}
        virtual void handleRightArrowKeyDownPress() {}

        virtual void handleUpArrowKeyUpRelease() {}
        virtual void handleDownArrowKeyUpRelease() {}
        virtual void handleLeftArrowKeyUpRelease() {}
        virtual void handleRightArrowKeyUpRelease() {}

        virtual void handleWKeyDownPress() {}
        virtual void handleAKeyDownPress() {}
        virtual void handleSKeyDownPress() {}
        virtual void handleDKeyDownPress() {}
        virtual void handleSpaceKeyDownPress() {}
        virtual void handleOneKeyDownPress() {}
        virtual void handleTwoKeyDownPress() {}
        virtual void handleThreeKeyDownPress() {}

        virtual void handleWKeyRelease() {}
        virtual void handleAKeyRelease() {}
        virtual void handleSKeyRelease() {}
        virtual void handleDKeyRelease() {}
        int speed = 3;

    private:
        SDL_Texture *spriteTexture;
        int xPosition;
        int yPosition;
        //MovableSprite(const MovableSprite &) = delete;
        //MovableSprite &operator=(const MovableSprite &) = delete;
    };

}

#endif