#ifndef PLAYERASSETS_H
#define PLAYERASSETS_H
#include <string>
#include <vector>

/**
 * Singelton class handling all assets related to Player class using Strategy pattern
 */
class PlayerAssets
{
public:
    virtual ~PlayerAssets() {}
    virtual void destroyInstance() {}
    const std::string getHeartContainerAssetPath() const;
    const std::string getEmptyHeartContainerAssetPath() const;
    const std::string getNextElementSwitchAssetPath();
    const virtual std::string getNextRightWalkAssetPath();
    const virtual std::string getNextLeftWalkAssetPath();
    const virtual std::string getNextRightPowerThrowAssetPath();
    const virtual std::string getNextLeftPowerThrowAssetPath();
    const virtual std::string getStationaryRightAssetPath();
    const virtual std::string getStationaryLeftAssetPath();
protected:
    PlayerAssets();
    const std::string getPathSuffix() const { return PATH_SUFFIX; }
private:
    void resetCounters();
    const std::string PATH_SUFFIX = ".png";
    std::string heartContainerAssetPath;
    std::string emptyHeartContainerAssetPath;
    const std::string getNextAssetPath(std::vector<std::string> paths, unsigned int assetCount);
    std::string stationaryRightAssetPath;
    std::string stationaryLeftAssetPath;
    std::vector<std::string> rightWalkAssetPaths;
    std::vector<std::string> leftWalkAssetPaths;
    std::vector<std::string> rightPowerThrowAssetPaths;
    std::vector<std::string> leftPowerThrowAssetPaths;
    std::string nextAssetPath;
    unsigned int rightWalkCount = 0;
    unsigned int leftWalkCount = 0;
    unsigned int rightPowerThrowCount = 0;
    unsigned int leftPowerThrowCount = 0;
    unsigned int lastAssetIndex;
};

#endif
