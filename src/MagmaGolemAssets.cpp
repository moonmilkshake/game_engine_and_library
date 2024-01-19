#include "MagmaGolemAssets.h"
#include "PlayerAssets.h"
#include <iostream>

MagmaGolemAssets* MagmaGolemAssets::instance = nullptr;

MagmaGolemAssets* MagmaGolemAssets::getInstance()
{
    if (!instance)
    {
        instance = new MagmaGolemAssets();
    }
    return instance;
}

const std::string MagmaGolemAssets::getStationaryRightAssetPath()
{
    return PlayerAssets::getStationaryRightAssetPath() + GOLEM_ID + getPathSuffix();
}

const std::string MagmaGolemAssets::getStationaryLeftAssetPath()
{
    return PlayerAssets::getStationaryLeftAssetPath() + GOLEM_ID + getPathSuffix();
}

const std::string MagmaGolemAssets::getNextRightWalkAssetPath()
{
    return PlayerAssets::getNextRightWalkAssetPath() + GOLEM_ID + getPathSuffix();
}

const std::string MagmaGolemAssets::getNextLeftWalkAssetPath()
{
    return PlayerAssets::getNextLeftWalkAssetPath() + GOLEM_ID + getPathSuffix();
}

const std::string MagmaGolemAssets::getNextRightPowerThrowAssetPath()
{
    return PlayerAssets::getNextRightPowerThrowAssetPath() + GOLEM_ID + getPathSuffix();
}

const std::string MagmaGolemAssets::getNextLeftPowerThrowAssetPath()
{
    return PlayerAssets::getNextLeftPowerThrowAssetPath() + GOLEM_ID + getPathSuffix();
}

void MagmaGolemAssets::destroyInstance()
{
    if (instance) {
        delete instance;
        instance = nullptr;
    }
}