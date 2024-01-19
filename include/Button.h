#ifndef BUTTON_H
#define BUTTON_H

#include "Component.h"
#include <SDL2/SDL.h>
#include <string>

// Spelmotor-klass
namespace crane
{
    class Button : public Component
    {
    public:
        Button(int x, int y, int width, int height, int weight, std::string upAssetPath, std::string downAssetPath);
        virtual ~Button() override;
        virtual void perform(Button *source) = 0;
        void mouseDown(const SDL_Event &) override;
        void mouseUp(const SDL_Event &) override;
        void draw() const override;

    protected:
        bool isDown = false;

    private:
        SDL_Texture *upIcon;
        SDL_Texture *downIcon;
        Button(const Button &) = delete;
        Button &operator=(const Button &) = delete;
    };
}

#endif
