#pragma once
#include <vector>
#include "../FBXModel.h"
struct Keyframe
{
    std::vector<std::shared_ptr<FBXModel>> modelsToAnimate;
    std::unordered_map<std::shared_ptr<FBXModel>,Transform> animateTransforms;
    float timeStamp;

    Keyframe(){};
    Keyframe(const std::vector<std::shared_ptr<FBXModel>> modelsToAnimate,const std::unordered_map<std::shared_ptr<FBXModel>,Transform> animateTransforms,const float timeStamp)
        : modelsToAnimate(modelsToAnimate), animateTransforms(animateTransforms), timeStamp(timeStamp) {}
    Keyframe(const std::unordered_map<std::shared_ptr<FBXModel>,Transform> animateTransforms,const float timeStamp)
        : animateTransforms(animateTransforms), timeStamp(timeStamp)
    {
        std::vector<std::shared_ptr<FBXModel>> models;
        for(auto pair : animateTransforms)
        {
            modelsToAnimate.push_back(pair.first);
        }
    }
};
