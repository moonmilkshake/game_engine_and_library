#include "StoneGolemAssets.h"
#include "PlayerAssets.h"
#include <iostream>

StoneGolemAssets* StoneGolemAssets::instance = nullptr;

StoneGolemAssets* StoneGolemAssets::getInstance()
{
    if (!instance)
    {
        instance = new StoneGolemAssets();
    }
    return instance;
}

const std::string StoneGolemAssets::getStationaryRightAssetPath()
{
    return PlayerAssets::getStationaryRightAssetPath() + GOLEM_ID + getPathSuffix();
}

const std::string StoneGolemAssets::getStationaryLeftAssetPath()
{
    return PlayerAssets::getStationaryLeftAssetPath() + GOLEM_ID + getPathSuffix();
}

const std::string StoneGolemAssets::getNextRightWalkAssetPath()
{
    return PlayerAssets::getNextRightWalkAssetPath() + GOLEM_ID + getPathSuffix();
}

const std::string StoneGolemAssets::getNextLeftWalkAssetPath()
{
    return PlayerAssets::getNextLeftWalkAssetPath() + GOLEM_ID + getPathSuffix();
}

const std::string StoneGolemAssets::getNextRightPowerThrowAssetPath()
{
    return PlayerAssets::getNextRightPowerThrowAssetPath() + GOLEM_ID + getPathSuffix();
}

const std::string StoneGolemAssets::getNextLeftPowerThrowAssetPath()
{
    return PlayerAssets::getNextLeftPowerThrowAssetPath() + GOLEM_ID + getPathSuffix();
}

void StoneGolemAssets::destroyInstance()
{
    if (instance) {
        delete instance;
        instance = nullptr;
    }
}