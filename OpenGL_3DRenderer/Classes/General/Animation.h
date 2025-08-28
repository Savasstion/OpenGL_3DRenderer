#pragma once
#include <unordered_map>
#include <vector>
#include "Keyframe.h"

struct Animation
{
    bool isPlaying = false;
    bool readyToPlay = false;
    bool isPaused = false;
    bool isLooped = true;
    float currentTime = 0;
    std::vector<std::shared_ptr<Keyframe>> keyframes;
    std::unordered_map<std::shared_ptr<FBXModel>, Transform> initialTransforms;
    std::unordered_map<std::shared_ptr<FBXModel>, Transform> transformBuffer;

    
};
