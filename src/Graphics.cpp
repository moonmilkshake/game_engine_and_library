#include "Constants.h"
#include "Graphics.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <algorithm>
#include "Component.h"

// Spelmotor-klass
namespace crane
{
    Graphics::Graphics()
    {
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        {
            std::cerr << "SDL_Init failed: " << SDL_GetError() << std::endl;
        }
        
        win = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1450, 1000, 0);
        if (!win)
        {
            std::cerr << "SDL_CreateWindow failed: " << SDL_GetError() << std::endl;
        }

        ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
        if (!ren)
        {
            std::cerr << "SDL_CreateRenderer failed: " << SDL_GetError() << std::endl;
        }

        if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
        {
            std::cerr << "IMG_Init failed: " << IMG_GetError() << std::endl;
        }

        if (Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 2048) < 0)
        {
            std::cerr << "Mix_OpenAudio failed: " << Mix_GetError() << std::endl;
        }

        SDL_GetWindowSizeInPixels(win, &screenWidth, &screenHeight);
    }

    void Graphics::playSound(const std::string &filePath)
    {
        Mix_Chunk *sound = Mix_LoadWAV(filePath.c_str());
        if (sound != nullptr)
        {
            Mix_PlayChannel(-1, sound, -1);
        }
    }

    /**
     * Method for setting screen to desired size
     */
    void Graphics::setScreenSize(int newScreenWidth, int newScreenHeight)
    {
        screenWidth = newScreenWidth;
        screenHeight = newScreenHeight;
        SDL_SetWindowSize(win, screenWidth, screenHeight);
    }

    int Graphics::getScreenHeight() const
    {
        return screenHeight;
    }

    int Graphics::getScreenWidth() const
    {
        return screenWidth;
    }

    void Graphics::loadBackground(const std::string &filePath)
    {
        backgroundTexture = loadTexture(filePath);
    }

    /**
     * Method that creates texture using renderer if surface can be created with file-path
     */
    SDL_Texture *Graphics::loadTexture(const std::string &filePath)
    {
        SDL_Texture *texture = nullptr;
        SDL_Surface *surface = IMG_Load(filePath.c_str());
        if (surface != nullptr)
        {
            texture = SDL_CreateTextureFromSurface(ren, surface);
            SDL_FreeSurface(surface);
        }
        return texture;
    }

    void Graphics::renderBackground()
    {
        SDL_RenderCopy(ren, backgroundTexture, nullptr, nullptr);
    }

    /**
     * Method for setting a custom background with path to desired image
     */
    void Graphics::setCustomBackground(const std::string &filePath)
    {
        loadBackground(filePath);
    }

    SDL_Renderer *Graphics::get_ren() const
    {
        return ren;
    }

    TTF_Font *Graphics::get_font() const
    {
        return font;
    }

    SDL_Window *Graphics::get_win() const
    {
        return win;
    }

    Graphics::~Graphics()
    {
        SDL_DestroyTexture(backgroundTexture);
        backgroundTexture = nullptr;
        Mix_FreeChunk(music);
        music = nullptr;
        Mix_CloseAudio();
        TTF_CloseFont(font);
        font = nullptr;
        SDL_DestroyWindow(win);
        win = nullptr;
        SDL_DestroyRenderer(ren);
        ren = nullptr;

        SDL_Quit();
        TTF_Quit();
        Mix_Quit();
    }

    Graphics graphic;

};