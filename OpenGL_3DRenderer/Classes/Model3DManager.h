#pragma once
#include <memory>
#include <set>
#include <vector>


#include "FBXModel.h"

class Model3DManager
{
public:
    static std::vector<std::shared_ptr<FBXModel>> sceneModels;
    
    static std::shared_ptr<FBXModel> CreateFBXModel(const char* filePath);
    static std::shared_ptr<FBXModel> CreateFBXModel(const char* filePath, Transform transform);
    static std::shared_ptr<FBXModel> CreateChildFBXModel(std::shared_ptr<FBXModel> parent,const char* filePath);
    static std::shared_ptr<FBXModel> CreateChildFBXModel(std::shared_ptr<FBXModel> parent,const char* filePath, Transform transform);
    static void DrawFBXModel(const std::shared_ptr<FBXModel> model);
    static void DrawFBXModelWithTransform(const std::shared_ptr<FBXModel> model);
    
};
