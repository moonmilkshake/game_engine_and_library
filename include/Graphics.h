#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

// Spelmotor-klass
namespace crane
{

    struct Graphics
    {
    public:
        Graphics();
        ~Graphics();
        SDL_Renderer *get_ren() const;
        TTF_Font *get_font() const;
        void renderBackground();
        void setCustomBackground(const std::string &filePath);
        int getScreenWidth() const;
        int getScreenHeight() const;
        void setScreenSize(int newScreenWidth, int newScreenHeight);
        void playSound(const std::string &filePath);
        SDL_Window *get_win() const;

    private:
        SDL_Texture *backgroundTexture;
        SDL_Texture *loadTexture(const std::string &filePath);
        void loadBackground(const std::string &filepath);
        SDL_Window *win;
        SDL_Renderer *ren;
        Mix_Chunk *music;
        TTF_Font *font;
        int screenWidth;
        int screenHeight;
    };

    extern Graphics graphic;

}

#endif