#include "GameEngine.h"
#include <SDL2/SDL.h>
#include "Graphics.h"
#include <vector>
#include "Component.h"
#include "ThrowableRock.h"
#include <iostream>
#include <algorithm>

using namespace std;
// Spelmotor-klass
namespace crane
{

#define FPS 60

    GameEngine::GameEngine() : gameRunning(false) {}

    void GameEngine::addGameComponent(Component *component)
    {
        addedGameComponent.push_back(component);
    }

    void GameEngine::removeGameComponent(Component *component)
    {
        if (std::find(removed.begin(), removed.end(), component) == removed.end())
        {
            removed.push_back(component);
        }
    }

    void GameEngine::addUIComponent(Component *component)
    {
        addedUiComponent.push_back(component);
    }

    void GameEngine::removeUIComponent(Component *component)
    {
        if (std::find(removed.begin(), removed.end(), component) == removed.end())
        {
            removed.push_back(component);
        }
    }

    void GameEngine::startGame()
    {
        gameRunning = true;
    }

    bool GameEngine::getGameRunning() const
    {
        return gameRunning;
    }

    void GameEngine::togglePause()
    {
        gamePaused = !gamePaused;
    }

    void GameEngine::setQuit(bool quit)
    {
        this->quit = quit;
    }

    bool CompareComponentWeight(Component* a, Component* b)
    {
        return a->getWeight() < b->getWeight();
    }

    void GameEngine::run()
    {
        Uint32 tickInterval = 1000 / FPS;

        while (!quit)
        {

            Uint32 nextTick = SDL_GetTicks() + tickInterval;
            SDL_Event event;

            if (gameRunning)
            {
                std::sort(gameComponents.begin(), gameComponents.end(), CompareComponentWeight);
            }

            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_QUIT)
                {
                    quit = true;
                }

                if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
                {
                    togglePause();
                }

                // Handle key events for game components
                if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
                {
                    for (Component *c : gameComponents)
                    {
                        if (event.type == SDL_KEYDOWN)
                        {
                            c->keyDown(event);
                        }
                        else if (event.type == SDL_KEYUP)
                        {
                            c->keyUp(event);
                        }
                    }
                }
                // Forward mouse events to UI components
                for (Component *c : uiComponents)
                {
                    if (event.type == SDL_MOUSEBUTTONDOWN)
                    {
                        c->mouseDown(event);
                    }
                    else if (event.type == SDL_MOUSEBUTTONUP)
                    {
                        c->mouseUp(event);
                    }
                }
            }
            // Loop through to check for collisions and lets each component handle it
            for (Component *firstC : gameComponents)
            {
                for (Component *secondC : gameComponents)
                {
                    if (firstC != secondC)
                    {
                        if (firstC->checkCollision(secondC))
                        {
                            firstC->handleCollision(secondC);
                        }
                    }
                }
            }

            // Update game-components if the game is running
            if (gameRunning && !gamePaused)
            {
                for (Component *c : gameComponents)
                {
                    c->tick();
                }
            }

            // Update UI-components if the game isn't running
            if (!gameRunning)
            {
                for (Component *c : uiComponents)
                {
                    c->tick();
                }
            }

            // Add new UI-components
            for (Component *c : addedUiComponent)
            {
                uiComponents.push_back(c);
            }
            addedUiComponent.clear();

            // Add new game-components
            for (Component *c : addedGameComponent)
            {
                gameComponents.push_back(c);
            }
            addedGameComponent.clear();

            // Remove game-components
            for (Component *c : removed)
            {
                for (vector<Component *>::iterator i = gameComponents.begin();
                     i != gameComponents.end();)
                {
                    if (*i == c)
                    {
                        delete *i;
                        i = gameComponents.erase(i);
                    }
                    else
                    {
                        i++;
                    }
                }
            }
            // Remove UI-components
            for (Component *c : removed)
            {
                for (vector<Component *>::iterator i = uiComponents.begin();
                     i != uiComponents.end();)
                {
                    if (*i == c)
                    {
                        delete *i;
                        i = uiComponents.erase(i);
                    }
                    else
                    {
                        i++;
                    }
                }
            }
            removed.clear();

            // Set renderer to color white and clear the renderer
            SDL_SetRenderDrawColor(graphic.get_ren(), 255, 255, 255, 255);
            SDL_RenderClear(graphic.get_ren());

            graphic.renderBackground();

            // Render game-components if the game is running
            if (gameRunning)
            {
                for (Component *c : gameComponents)
                {
                    c->draw();
                }
            }

            // Render UI-components if the game is not running
            if (!gameRunning || gamePaused)
            {
                for (Component *c : uiComponents)
                {
                    c->draw();
                }
            }

            SDL_RenderPresent(graphic.get_ren());

            // Delay to maintain set frame-rate
            int delay = nextTick - SDL_GetTicks();
            if (delay > 0)
            {
                SDL_Delay(delay);
            }
        }
    }

    /**
     * Clean up all components
     */
    GameEngine::~GameEngine()
    {
        for (Component *c : gameComponents)
        {
            if (c != nullptr)
            {
                delete c;
            }
        }
        for (Component *c : uiComponents)
        {
            if (c != nullptr)
            {
                delete c;
            }
        }
        for (Component *c : addedGameComponent)
        {
            if (c != nullptr)
            {
                delete c;
            }
        }
        for (Component *c : addedUiComponent)
        {
            if (c != nullptr)
            {
                delete c;
            }
        }
        for (Component *c : removed)
        {
            if (c != nullptr)
            {
                delete c;
            }
        }

        gameComponents.clear();
        uiComponents.clear();
        addedGameComponent.clear();
        addedUiComponent.clear();
        removed.clear();
    }

}