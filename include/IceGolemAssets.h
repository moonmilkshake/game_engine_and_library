#ifndef ICEGOLEMASSETS_H
#define ICEGOLEMASSETS_H
#include "PlayerAssets.h"
#include <vector>
#include <string>

/**
 * Singelton class handling Ice Golem assets related to Player class
 */
class IceGolemAssets : public PlayerAssets
{
public:
    static IceGolemAssets* getInstance();
    const std::string getNextRightWalkAssetPath() override;
    const std::string getNextLeftWalkAssetPath() override;
    const std::string getNextRightPowerThrowAssetPath() override;
    const std::string getNextLeftPowerThrowAssetPath() override;
    const std::string getStationaryRightAssetPath() override;
    const std::string getStationaryLeftAssetPath() override;
    void destroyInstance() override;
protected:
private:
    static IceGolemAssets* instance;
    IceGolemAssets() : PlayerAssets() {}
    const std::string GOLEM_ID = "ice";
};

#endif
