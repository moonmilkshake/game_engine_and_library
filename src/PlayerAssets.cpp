#include "PlayerAssets.h"
#include <string>
#include <vector>

PlayerAssets::PlayerAssets()
{
    stationaryRightAssetPath = "/images/golem_standing_right_";
    stationaryLeftAssetPath = "/images/golem_standing_left_";
    heartContainerAssetPath = "images/heart";
    emptyHeartContainerAssetPath = "images/empty_heart";

    for (int i = 1; i < 12; i++)
    {
        rightPowerThrowAssetPaths.push_back("images/golem_powerthrow_right/golem_power_throw_right_" + std::to_string(i) + "_");
        leftPowerThrowAssetPaths.push_back("images/golem_powerthrow_left/golem_power_throw_left_" + std::to_string(i) + "_");
    }
    for (int i = 1; i < 25; i++)
    {
        rightWalkAssetPaths.push_back("images/golem_rightwalk/golem_walking_right_" + std::to_string(i) + "_");
        leftWalkAssetPaths.push_back("images/golem_leftwalk/golem_walking_left_" + std::to_string(i) + "_");
    }
}

    
const std::string PlayerAssets::getHeartContainerAssetPath() const
{
    return heartContainerAssetPath + getPathSuffix();
}

const std::string PlayerAssets::getEmptyHeartContainerAssetPath() const
{
    return emptyHeartContainerAssetPath + getPathSuffix();
}

const std::string PlayerAssets::getStationaryRightAssetPath()
{
    resetCounters();
    return stationaryRightAssetPath;
}

const std::string PlayerAssets::getStationaryLeftAssetPath()
{
    resetCounters();
    return stationaryLeftAssetPath;
}

const std::string PlayerAssets::getNextAssetPath(std::vector<std::string> paths, unsigned int assetCount)
{
    nextAssetPath = paths.at(assetCount);
    lastAssetIndex = paths.size() - 1;
    return nextAssetPath;
}

const std::string PlayerAssets::getNextRightWalkAssetPath()
{
    getNextAssetPath(rightWalkAssetPaths, rightWalkCount);
    rightWalkCount = (rightWalkCount == lastAssetIndex) ? 0 : rightWalkCount + 1;
    return nextAssetPath;
}

const std::string PlayerAssets::getNextLeftWalkAssetPath()
{
    getNextAssetPath(leftWalkAssetPaths, leftWalkCount);
    leftWalkCount = (leftWalkCount == lastAssetIndex) ? 0 : leftWalkCount + 1;
    return nextAssetPath;
}

const std::string PlayerAssets::getNextRightPowerThrowAssetPath()
{
    getNextAssetPath(rightPowerThrowAssetPaths, rightPowerThrowCount);
    rightPowerThrowCount = (rightPowerThrowCount == lastAssetIndex) ? lastAssetIndex : rightPowerThrowCount + 1;
    return nextAssetPath;
}

const std::string PlayerAssets::getNextLeftPowerThrowAssetPath()
{
    getNextAssetPath(leftPowerThrowAssetPaths, leftPowerThrowCount);
    leftPowerThrowCount = (leftPowerThrowCount == lastAssetIndex) ? lastAssetIndex : leftPowerThrowCount + 1;
    return nextAssetPath;
}

void PlayerAssets::resetCounters()
{
    rightWalkCount = 0;
    leftWalkCount = 0;
    leftPowerThrowCount = 0;
    rightPowerThrowCount = 0;
}
