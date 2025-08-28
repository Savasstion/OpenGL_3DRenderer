#include "FBXModel.h"

#include "Model3DManager.h"
#include "../Util/UtilityFunctions.h"
//#include <fstream>
//#include <iostream>


FBXModel::FBXModel(const char* filePath)
{
    objectLoaded = false;
    this->transform = Transform();
    fileName = filePath;

    if (!fileName.empty())
        LoadFBX(fileName.data());
}

FBXModel::FBXModel(const char* filePath, const Transform transform)
{
    objectLoaded = false;
    this->transform = transform;
    fileName = filePath;

    if (!fileName.empty())
        LoadFBX(fileName.data());
}


bool FBXModel::LoadFBX(const char* filePath)
{
    FbxManager* manager = FbxManager::Create();
    if(!manager)
        return false;
    
    FbxIOSettings* ios = FbxIOSettings::Create(manager, IOSROOT);
    if(!ios)
        return false;
    
    manager->SetIOSettings(ios);

    FbxImporter* importer = FbxImporter::Create(manager, "");
    if(!importer)
        return false;
    
    if (!importer->Initialize(filePath, -1, manager->GetIOSettings())) {
        //std::cerr << "Error initializing FBX importer: " << importer->GetStatus().GetErrorString() << std::endl;
        return false;
    }

    FbxScene* scene = FbxScene::Create(manager, "MyScene");
    if(!scene)
        return false;
    
    importer->Import(scene);

    // Collect vertices
    FbxNode* rootNode = scene->GetRootNode();
    if (rootNode)
    {
        for (int i = 0; i < rootNode->GetChildCount(); ++i)
        {
            ProcessNode(rootNode->GetChild(i), polygons);
        }
    }

    //std::cout << "Loaded " << vertices.size() << " vertices." << std::endl;

    //write string result to a text file
    // 
    // Create and open a text file
    //std::ofstream MyFile("log.txt");

    // Write to the file
    //MyFile << "Loaded " << vertices.size() << " vertices.\n";

    // Close the file
    //MyFile.close();

    objectLoaded = true;
    
    // Cleanup
    importer->Destroy();
    manager->Destroy();

    return true;
    
}

bool FBXModel::LoadFBX(const char* filePath, Transform transform)
{
    this->transform = transform;
    
    FbxManager* manager = FbxManager::Create();
    if(!manager)
        return false;
    
    FbxIOSettings* ios = FbxIOSettings::Create(manager, IOSROOT);
    if(!ios)
        return false;
    
    manager->SetIOSettings(ios);

    FbxImporter* importer = FbxImporter::Create(manager, "");
    if(!importer)
        return false;
    
    if (!importer->Initialize(filePath, -1, manager->GetIOSettings())) {
        //std::cerr << "Error initializing FBX importer: " << importer->GetStatus().GetErrorString() << std::endl;
        return false;
    }

    FbxScene* scene = FbxScene::Create(manager, "MyScene");
    if(!scene)
        return false;
    
    importer->Import(scene);

    // Collect vertices
    FbxNode* rootNode = scene->GetRootNode();
    if (rootNode)
    {
        for (int i = 0; i < rootNode->GetChildCount(); ++i)
        {
            ProcessNode(rootNode->GetChild(i), polygons);
        }
    }

    //std::cout << "Loaded " << vertices.size() << " vertices." << std::endl;

    //write string result to a text file
    // 
    // Create and open a text file
    //std::ofstream MyFile("log.txt");

    // Write to the file
    //MyFile << "Loaded " << vertices.size() << " vertices.\n";

    // Close the file
    //MyFile.close();

    objectLoaded = true;
    
    // Cleanup
    importer->Destroy();
    manager->Destroy();

    return true;
    
}

void FBXModel::GetPolygonsFromMesh(FbxMesh* mesh, std::vector<PolygonFBX>& polygons)
{
    int polygonCount = mesh->GetPolygonCount();
    int vertexCount = mesh->GetControlPointsCount();
    auto controlPoints = mesh->GetControlPoints();

    FbxStringList uvSetNames;
    mesh->GetUVSetNames(uvSetNames);

    for (int i = 0; i < polygonCount; i++)
    {
        int polygonSize = mesh->GetPolygonSize(i);
        std::vector<VertexFBX> polygonVertices;
        
        for (int j = 0; j < polygonSize; j++)
        {
            int controlPointIndex = mesh->GetPolygonVertex(i, j);

            // Get position
            FbxVector4 position = controlPoints[controlPointIndex];
            //  Convert position value range to OpenGL
            position.mData[0] *= fbxToOpenGLModelSizeRatio;
            position.mData[1] *= fbxToOpenGLModelSizeRatio;
            position.mData[2] *= fbxToOpenGLModelSizeRatio;
            position.mData[3] *= fbxToOpenGLModelSizeRatio;

            // Get normal
            FbxVector4 normal;
            mesh->GetPolygonVertexNormal(i, j, normal);
            auto nX = normal.mData[0];
            auto nY = normal.mData[1];
            auto nZ = normal.mData[2];
            auto nW = normal.mData[3];
            
            double magnitude = sqrt(nX*nX + nY*nY + nZ*nZ + nW*nW); //Computes sqrt(x^2 + y^2 + z^2 + w^2)
            if(magnitude!=0)
            {
                //  normalize the vector just in case it weren't normalized before
                normal.mData[0] /= magnitude;
                normal.mData[1] /= magnitude;
                normal.mData[2] /= magnitude;
                normal.mData[3] /= magnitude;
            }

            // Get UV
            FbxVector2 uv(0, 0);
            bool unmapped;
            if (uvSetNames.GetCount() > 0)
            {
                mesh->GetPolygonVertexUV(i, j, uvSetNames[0], uv, unmapped);
            }

            // Store vertex
            polygonVertices.emplace_back(position, normal, uv);
        }
        
        auto polygonColor = Color(UtilityFunctions::GenerateRandomDouble(0,1), UtilityFunctions::GenerateRandomDouble(0,1), UtilityFunctions::GenerateRandomDouble(0,1));
        polygons.emplace_back(polygonVertices, polygonColor);
    }
}

void FBXModel::ProcessNode(FbxNode* node, std::vector<PolygonFBX>& polygons)
{
    FbxMesh* mesh = node->GetMesh();
    if (mesh)
    {
        GetPolygonsFromMesh(mesh, polygons);
    }

    //  Process for its children too
    for (int i = 0; i < node->GetChildCount(); ++i)
    {
        ProcessNode(node->GetChild(i), polygons);
    }
}

// FBXModel* FBXModel::CreateChild(const char* filePath)
// {
//     //  in case in the future we like to have a ModelManager that stores all the model in one vector, remove constructor here
//     Model3DManager::CreateFBXModel(filePath);
//     auto child = &Model3DManager::sceneModels.back();
//
//     child->parent = this;
//     children.push_back(child);
//     return child;
// }
//
// FBXModel* FBXModel::CreateChild(const char* filePath, Transform transform)
// {
//     //  in case in the future we like to have a ModelManager that stores all the model in one vector, remove constructor here
//     Model3DManager::CreateFBXModel(filePath);
//     auto child = &Model3DManager::sceneModels.back();
//     
//     child->transform = transform;
//     child->parent = this;
//     children.push_back(child);
//     return child;
// }




