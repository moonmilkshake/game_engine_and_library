#ifndef ANIMATIONHANDLER_H
#define ANIMATIONHANDLER_H
#include <vector>
#include <string>

class AnimationHandler
{
public:
    AnimationHandler(int animDelay, int animCount, int lastAssetInd);
    AnimationHandler(int animDelay, int animCount, int lastAssetInd, int loops);
    bool timeForNextAsset();
    bool timeForRemoval();
    int getAnimationCount() const { return animationCount; }
    void addAssets(std::vector<std::string>& assets, int startingIndex, int size, std::string path);
    void resetValuesToOriginal();
protected:

private:
    void setOriginalValues(bool infinite, int nrOfLoops);
    int originalAnimationDelayCounter;
    int originalAnimationDelay;
    int originalAnimationCount;
    int originalLastAssetIndex;
    int originalNrOfLoops;
    bool originalInfiniteLoop;
    int animationDelayCounter = 0;
    int animationDelay;
    int animationCount;
    int lastAssetIndex;
    int nrOfLoops = -1;
    bool infiniteLoop = false;
};


#endif