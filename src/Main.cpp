#include "Player.h"
#include "Constants.h"
#include "GameEngine.h"
#include "Graphics.h"
#include "FireSpirit.h"
#include "IceBlob.h"
#include "Wraith.h"
#include "ImmovableSprite.h"
#include "Button.h"
#include <string>
#include <iostream>

// Spel-klass
using namespace crane;

GameEngine engine;
/**
 * Class for creating a resume-button, used for pausing game
 */
class StartButton : public Button
{
public:
    StartButton(int weight, GameEngine *engine, std::string upAssetPath, std::string downAssetPath)
        : Button(450, 200, 150, 70, weight, upAssetPath, downAssetPath), gameEngine(engine) {}

    void perform(Button *source) override
    {
        gameEngine->togglePause();
    }

private:
    GameEngine *gameEngine;
};

/**
 * Class for creating a stop-button, used for shutting down program via GUI menu
 */
class StopButton : public Button
{
public:
    StopButton(int weight, GameEngine *engine, std::string upAssetPath, std::string downAssetPath)
        : Button(450, 300, 150, 70, weight, upAssetPath, downAssetPath), gameEngine(engine) {}

    void perform(Button *source) override
    {
        gameEngine->setQuit(true);
    }

private:
    GameEngine *gameEngine;
};

/**
 * Class for creating a start-button, used for starting game
 */
class NewGameButton : public Button
{
public:
    NewGameButton(int weight, GameEngine *engine, std::string upAssetPath, std::string downAssetPath)
        : Button(425, 300, 250, 70, weight, upAssetPath, downAssetPath), gameEngine(engine) {}

    void perform(Button *source) override
    {
        gameEngine->startGame();
        gameEngine->removeUIComponent(this);

        StartButton *startButton = new StartButton(0, &engine, constants::gResPath + "images/start_button.png", constants::gResPath + "images/start_buttonDown.png");
        StopButton *stopButton = new StopButton(0, &engine, constants::gResPath + "images/stop_button.png", constants::gResPath + "images/stop_button.png");

        engine.addUIComponent(startButton);
        engine.addUIComponent(stopButton);
    }

private:
    GameEngine *gameEngine;
};

int main(int argc, char **argv)
{
    // Set up window and background
    graphic.setScreenSize(1450, 1000);
    graphic.setCustomBackground(constants::gResPath + "images/grassBackground.png");

    // Set up UI
    NewGameButton *newGameButton = new NewGameButton(0, &engine, constants::gResPath + "images/new_game_button.png", constants::gResPath + "images/new_game_ButtonDown.png");
    engine.addUIComponent(newGameButton);

    // Set up player
    Player *player = Player::create(700, 450, 65, 105, 3, constants::gResPath + "images/golem_standing_right_stone.png", &engine);
    engine.addGameComponent(player);

    // Set up music
    //graphic.playSound(constants::gResPath + "sounds/jungle.wav");

    // Set up Immovable Sprites
    ImmovableSprite *rock = ImmovableSprite::getInstance(90, 90, 50, 50, 1, constants::gResPath + "images/rock.png");
    engine.addGameComponent(rock);

    engine.addGameComponent(Wraith::create(50, 350, 60, 90, 3, &engine));
    engine.addGameComponent(IceBlob::create(50, 625, 70, 45, 3, &engine));
    engine.addGameComponent(FireSpirit::create(300, 350, 105, 40, 3, &engine));


    engine.run();

    player->destroyInstance();

    return 0;
}
