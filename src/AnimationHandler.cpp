#include "AnimationHandler.h"
#include <vector>
#include <string>

using namespace std;

AnimationHandler::AnimationHandler(int animDelay, int animCount, int lastAssetInd) : 
                    animationDelay(animDelay), animationCount(animCount), lastAssetIndex(lastAssetInd), infiniteLoop(true)
{
    setOriginalValues(true, -1);
}

AnimationHandler::AnimationHandler(int animDelay, int animCount, int lastAssetInd, int loops) : 
                    animationDelay(animDelay), animationCount(animCount), lastAssetIndex(lastAssetInd), nrOfLoops(loops)
{
    setOriginalValues(false, loops);
}


void AnimationHandler::setOriginalValues(bool infinite, int nrOfLoops)
{
    originalAnimationDelayCounter = animationDelayCounter;
    originalAnimationDelay = animationDelay;
    originalAnimationCount = animationCount;
    originalLastAssetIndex = lastAssetIndex;
    originalNrOfLoops = nrOfLoops;
    originalInfiniteLoop = infiniteLoop;
}

void AnimationHandler::resetValuesToOriginal()
{
    animationDelayCounter = originalAnimationDelayCounter;
    animationDelay = originalAnimationDelay;
    animationCount = originalAnimationCount;
    lastAssetIndex = originalLastAssetIndex;
    nrOfLoops = originalNrOfLoops;
    infiniteLoop = originalInfiniteLoop;    
}

void AnimationHandler::addAssets(vector<string>& assets, int startingIndex, int size, string path)
{
    for (int i = startingIndex; i <= size; ++i)
    {
        assets.push_back(path + std::to_string(i));
    }
}

bool AnimationHandler::timeForNextAsset()
{
    bool isTime = animationDelayCounter >= animationDelay;
    if (isTime)
    {
        animationDelayCounter = 0;
        ++animationCount;
        if (animationCount > lastAssetIndex)
        {
            animationCount = 0;
                if (!infiniteLoop)
                {
                    --nrOfLoops;
                }
        }
    }
    else
    {
        ++animationDelayCounter;
    }
    return isTime && nrOfLoops != 0;
}

bool AnimationHandler::timeForRemoval()
{
    return nrOfLoops < 1;
}