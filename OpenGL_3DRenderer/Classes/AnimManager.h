#pragma once
#include <vector>

#include "General/Animation.h"
#include "General/Transform.h"

class AnimManager
{
public:
    static std::vector<std::shared_ptr<Animation>> sceneAnimations;
    static std::shared_ptr<Animation> currentAnim;

    static void ToggleAnimation(unsigned int animIndex, bool isToggledOn);
    static void ToggleOffAllAnimations();
    static void InitAnimationBuffer(std::shared_ptr<Animation> anim);
    static void TogglePause(std::shared_ptr<Animation> anim, bool isPaused);
    static void UpdateAnimations(float deltaTime);
    static void UpdateAnimation(std::shared_ptr<Animation> anim, float deltaTime);
    static std::shared_ptr<Animation> CreateAnimation();
    static std::shared_ptr<Keyframe> CreateKeyframe(std::shared_ptr<Animation> parentAnim, std::unordered_map<std::shared_ptr<FBXModel>,Transform> meshAndTransformMap, float timeStamp);
    
};
