#ifndef MAGMAGOLEMASSETS_H
#define MAGMAGOLEMASSETS_H
#include "PlayerAssets.h"
#include <vector>
#include <string>

/**
 * Singelton class handling Magma Golem assets related to Player class
 */
class MagmaGolemAssets : public PlayerAssets
{
public:
    static MagmaGolemAssets* getInstance();
    const std::string getNextRightWalkAssetPath() override;
    const std::string getNextLeftWalkAssetPath() override;
    const std::string getNextRightPowerThrowAssetPath() override;
    const std::string getNextLeftPowerThrowAssetPath() override;
    const std::string getStationaryRightAssetPath() override;
    const std::string getStationaryLeftAssetPath() override;
    void destroyInstance() override;
protected:
private:
    static MagmaGolemAssets* instance;
    MagmaGolemAssets() : PlayerAssets() {}
    const std::string GOLEM_ID = "magma";
};

#endif
