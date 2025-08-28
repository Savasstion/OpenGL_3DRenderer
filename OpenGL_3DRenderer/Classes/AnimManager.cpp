#include "AnimManager.h"

#include <set>

#include "../Util/UtilityFunctions.h"

std::vector<std::shared_ptr<Animation>> AnimManager::sceneAnimations;
std::shared_ptr<Animation> AnimManager::currentAnim;


void AnimManager::ToggleAnimation(unsigned int animIndex, bool isToggledOn)
{
    if(isToggledOn)
    {
        ToggleOffAllAnimations();
        sceneAnimations[animIndex]->isPlaying = true;
        currentAnim = sceneAnimations[animIndex];
    }
    else
    {
        sceneAnimations[animIndex]->currentTime = 0;
        sceneAnimations[animIndex]->isPlaying = false;
        sceneAnimations[animIndex]->readyToPlay = false;
    }
}

void AnimManager::ToggleOffAllAnimations()
{
    for(auto& anim : sceneAnimations)
    {
        anim->currentTime = 0;
        anim->isPlaying = false;
        anim->readyToPlay = false;
    }
}

void AnimManager::InitAnimationBuffer(std::shared_ptr<Animation> anim)
{
    //  get all meshes/models from all the keyframes with no duplicates
    std::set<std::shared_ptr<FBXModel>> modelPtrSet;
    for(auto keyframe : anim->keyframes)
    {
        for(auto meshPtr : keyframe->modelsToAnimate)
        {
            modelPtrSet.insert(meshPtr);
        }
    }

    for(auto meshPtr : modelPtrSet)
    {
        //  init transform buffers with current mesh transforms
        anim->initialTransforms[meshPtr] = meshPtr->transform;
        anim->transformBuffer[meshPtr] = meshPtr->transform;
    }
    
}

void AnimManager::TogglePause(std::shared_ptr<Animation> anim, bool isPaused)
{
    anim->isPaused = isPaused;
}

void AnimManager::UpdateAnimations(float deltaTime)
{
    for(unsigned long long i = 0; i < sceneAnimations.size(); i++)
    {
        if(sceneAnimations[i]->isPlaying)
        {
            if(!sceneAnimations[i]->readyToPlay)   //  dont animate using the prev deltaTime at the same frame where isPlaying is toggled on
            {
                //  this will be the first processes an anim will do
                sceneAnimations[i]->readyToPlay = true;
                InitAnimationBuffer(sceneAnimations[i]);
            }
            else
            {
                if(!sceneAnimations[i]->isPaused)
                    UpdateAnimation(sceneAnimations[i],deltaTime);
            }
                
        }
    }
}

void AnimManager::UpdateAnimation(std::shared_ptr<Animation> anim, float deltaTime)
{
    anim->currentTime += deltaTime;
    float totalAnimTime = anim->keyframes.back()->timeStamp;

    //  if a loop happens, reset all mesh/model to their initial transforms
    if(anim->currentTime > totalAnimTime && anim->isLooped)
    {

        for(auto pair : anim->initialTransforms)
        {
            pair.first->transform = pair.second;
        }

        //  does the same as modulus but for floats
        while(anim->currentTime >= totalAnimTime)
        {
            anim->currentTime -= totalAnimTime;
        }
    }
    

    if(anim->currentTime < totalAnimTime || anim->isLooped)    //  if not looped, and already finished the anim, dont bother doing this code
    {
        //  update transform buffers with all prev keyframes played
        //  PS : If want to sacrifice memory for less processing time, we can store every mesh transforms in each keyframe and just search for just that one keyframe right before the current time
        for(auto& keyframe : anim->keyframes)
        {
            if(keyframe->timeStamp < anim->currentTime)
            {
                for(auto mesh : keyframe->modelsToAnimate)
                {
                    anim->transformBuffer[mesh] = keyframe->animateTransforms[mesh];
                }
            }
        }


        //  apply all the transforms in the buffer to ensure all mesh/model is updated
        for(auto pair : anim->transformBuffer)
        {
            pair.first->transform = pair.second;
        }
    

        Keyframe startFrame,endFrame;
        //  search left to right of the keyframe vector for the start and end frame
        //  PS : make sure the timestamps are sequentially incremental
        for(unsigned long long i = 0; i < anim->keyframes.size(); i++)
        {
            if(anim->keyframes[i]->timeStamp >= anim->currentTime && anim->keyframes[i]->timeStamp != 0)
            {
                endFrame = *anim->keyframes[i];
                startFrame = *anim->keyframes[i-1];
                break;
            }
        }

        //  anim interpolate here
        for(auto modelPtr : endFrame.modelsToAnimate)
        {
            modelPtr->transform = UtilityFunctions::LerpTransform(modelPtr->transform, endFrame.animateTransforms[modelPtr], (anim->currentTime - startFrame.timeStamp) / (endFrame.timeStamp - startFrame.timeStamp));
        }
        
    }

    if(anim->currentTime >= totalAnimTime && !anim->isLooped)
    {
        anim->currentTime = totalAnimTime;
        anim->isPlaying = false;
        anim->readyToPlay = false;
    }
    
    
}


std::shared_ptr<Animation> AnimManager::CreateAnimation()
{
    auto anim = std::make_shared<Animation>();
    sceneAnimations.push_back(anim);
    return anim;
}

std::shared_ptr<Keyframe> AnimManager::CreateKeyframe(std::shared_ptr<Animation> parentAnim,
    std::unordered_map<std::shared_ptr<FBXModel>,Transform> meshAndTransformsMap , float timeStamp)
{
    auto kf = std::make_shared<Keyframe>(meshAndTransformsMap,timeStamp);
    parentAnim->keyframes.push_back(kf);
    return kf;
}

