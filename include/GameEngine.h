#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "Component.h"
#include <vector>

// Spelmotor-klass
namespace crane
{

    class GameEngine
    {
    public:
        void run();

        void addGameComponent(Component *component);
        void removeGameComponent(Component *component);
        void addUIComponent(Component *component);
        void removeUIComponent(Component *component);
        void startGame();
        void togglePause();
        bool getGameRunning() const;
        void setQuit(bool quit);
        GameEngine();
        ~GameEngine();

    private:
        std::vector<Component *> gameComponents;
        std::vector<Component *> uiComponents;
        std::vector<Component *> addedGameComponent;
        std::vector<Component *> addedUiComponent;
        std::vector<Component *> removed;
        bool gameRunning = false;
        bool gamePaused = false;
        bool quit = false;
    };

}

#endif // GAMEENGINE_H
