#ifndef  FBXLOADER_H
#define FBXLOADER_H
#include <string>
#include <vector>
#include <cmath>
#include <fbxsdk.h>
#include <memory>

#include "General/PolygonFBX.h"
#include "General/Texture.h"
#include "General/Transform.h"

#define fbxToOpenGLModelSizeRatio 1/600.0;

class FBXModel
{
public:
    std::vector<PolygonFBX> polygons;
    Transform transform;
    std::shared_ptr<FBXModel> parent = nullptr;
    std::vector<std::shared_ptr<FBXModel>> children;
    bool isActive = true;
    
    FBXModel(const char* filePath);
    FBXModel(const char* filePath, Transform transform);
    //virtual ~FBXLoader();

    bool LoadFBX(const char* filePath);
    bool LoadFBX(const char* filePath, const Transform transform);
    static void GetPolygonsFromMesh(FbxMesh* mesh, std::vector<PolygonFBX>& polygons);
    static void ProcessNode(FbxNode* node, std::vector<PolygonFBX>& polygons);
    // FBXModel* CreateChild(const char* filePath);
    // FBXModel* CreateChild(const char* filePath, Transform transform);
    
private:
    std::string fileName;
    bool objectLoaded;

};

#endif

