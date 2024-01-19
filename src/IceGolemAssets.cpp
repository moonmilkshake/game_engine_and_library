#include "IceGolemAssets.h"
#include "PlayerAssets.h"
#include <iostream>

IceGolemAssets* IceGolemAssets::instance = nullptr;

IceGolemAssets* IceGolemAssets::getInstance()
{
    if (!instance)
    {
        instance = new IceGolemAssets();
    }
    return instance;
}

const std::string IceGolemAssets::getStationaryRightAssetPath()
{
    return PlayerAssets::getStationaryRightAssetPath() + GOLEM_ID + getPathSuffix();
}

const std::string IceGolemAssets::getStationaryLeftAssetPath()
{
    return PlayerAssets::getStationaryLeftAssetPath() + GOLEM_ID + getPathSuffix();
}

const std::string IceGolemAssets::getNextRightWalkAssetPath()
{
    return PlayerAssets::getNextRightWalkAssetPath() + GOLEM_ID + getPathSuffix();
}

const std::string IceGolemAssets::getNextLeftWalkAssetPath()
{
    return PlayerAssets::getNextLeftWalkAssetPath() + GOLEM_ID + getPathSuffix();
}

const std::string IceGolemAssets::getNextRightPowerThrowAssetPath()
{
    return PlayerAssets::getNextRightPowerThrowAssetPath() + GOLEM_ID + getPathSuffix();
}

const std::string IceGolemAssets::getNextLeftPowerThrowAssetPath()
{
    return PlayerAssets::getNextLeftPowerThrowAssetPath() + GOLEM_ID + getPathSuffix();
}

void IceGolemAssets::destroyInstance()
{
    if (instance) {
        delete instance;
        instance = nullptr;
    }
}