#ifndef PLAYER_H
#define PLAYER_H
#include "MovableSprite.h"
#include "ObstacleHandler.h"
#include "GameEngine.h"
#include "PlayerElement.h"
#include "StoneGolemAssets.h"
#include <functional>

// Implementering till spelet som hanterar spelaren
//Spel-klass
using namespace crane;

    class Player : public MovableSprite, public ObstacleHandler
    {
    public:
        static Player* create(int x, int y, int width, int height, int weight, std::string assetPath, GameEngine* eng);
        static Player* getInstance() { return instance; }
        static void destroyInstance();
        void tick() override;
        void handleCollision(const Component* other) override;
        virtual ~Player() override;
        int getPlayerXCenter();
        int getPlayerYCenter();
    protected:
        Player(int x, int y, int width, int height, int weight, std::string assetPath, GameEngine* eng);
    
        void handleUpArrowKeyDownPress() override;
        void handleDownArrowKeyDownPress() override;
        void handleLeftArrowKeyDownPress() override;
        void handleRightArrowKeyDownPress() override;
        void handleSpaceKeyDownPress() override;
        void handleOneKeyDownPress() override;
        void handleTwoKeyDownPress() override;
        void handleThreeKeyDownPress() override;

        void handleUpArrowKeyUpRelease() override;
        void handleDownArrowKeyUpRelease() override;
        void handleLeftArrowKeyUpRelease() override;
        void handleRightArrowKeyUpRelease() override;

        void handleWKeyDownPress() override;
        void handleAKeyDownPress() override;
        void handleSKeyDownPress() override;
        void handleDKeyDownPress() override;

        void handleWKeyRelease() override;
        void handleAKeyRelease() override;
        void handleSKeyRelease() override;
        void handleDKeyRelease() override;
    private:
        static Player* instance;
        const int DEFAULT_POWER_LEVEL = 25;
        const int DEFAULT_SPEED = 3;
        const int DEFAULT_LIFE = 3;
        const int SPECIAL_ATTACK_COOLDOWN_PERIOD = 300;
        const int ELEMENT_SWITCH_COOLDOWN_PERIOD = 60;

        std::vector<MovableSprite*> heartContainers;
        PlayerAssets* assetsInstance = StoneGolemAssets::getInstance();
        PlayerElement* elementInstance;
        GameEngine* engine;
        MovableSprite* heartContainerOne;
        MovableSprite* heartContainerTwo;
        MovableSprite* heartContainerThree;
        void checkForDeath();
        void animatePlayerWalking();
        void animatePowerThrowRight();
        void animatePowerThrowLeft();
        void incrementThrowPower();
        void resetAfterThrow();
        void handleLifeDisplay();
        void initiateAttack(AttackDirection direction);
        const std::string getCorrectStationaryAsset() const;
        void setUpPlayerUI();
        void initiateElementSwitchAnimation();
        void handleTimeTracking();
        void updateCooldown(bool& isReady, int& timeTracker, int cooldownPeriod, std::function<void()> onReady = nullptr);
        void animateSpecialAttackReady();
        void handleElementSwitch(PlayerElement* newElement, PlayerAssets* newAssets);
        void takeDamage(int damage);
        void resetSpeed();

        int life;
        int previousXVelocity = 3;
        int xVelocity = 0;
        int yVelocity = 0;
        int throwPower;
        int specialAttackTimeTracker = 0;
        bool specialAttackReady = true;
        int elementSwitchTimeTracker = 0;
        bool elementSwitchReady = true;
        Player(const Player&) = delete;
        Player& operator=(const Player&) = delete;
    };

#endif