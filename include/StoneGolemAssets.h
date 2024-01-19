#ifndef STONEGOLEMASSETS_H
#define STONEGOLEMASSETS_H
#include "PlayerAssets.h"
#include <vector>
#include <string>

/**
 * Singelton class handling Stone Golem assets related to Player class
 */
class StoneGolemAssets : public PlayerAssets
{
public:
    static StoneGolemAssets* getInstance();
    const std::string getNextRightWalkAssetPath() override;
    const std::string getNextLeftWalkAssetPath() override;
    const std::string getNextRightPowerThrowAssetPath() override;
    const std::string getNextLeftPowerThrowAssetPath() override;
    const std::string getStationaryRightAssetPath() override;
    const std::string getStationaryLeftAssetPath() override;
    void destroyInstance() override;
protected:
private:
    static StoneGolemAssets* instance;
    StoneGolemAssets() : PlayerAssets() {}
    const std::string GOLEM_ID = "stone";
};

#endif
