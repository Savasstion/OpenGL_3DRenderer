#include "Model3DManager.h"
#include <Windows.h>
#include <gl/GL.h>


std::vector<std::shared_ptr<FBXModel>> Model3DManager::sceneModels;


std::shared_ptr<FBXModel> Model3DManager::CreateFBXModel(const char* filePath)
{
    auto model = std::make_shared<FBXModel>(filePath);
    sceneModels.push_back(model);
    return sceneModels.back();
}


std::shared_ptr<FBXModel> Model3DManager::CreateFBXModel(const char* filePath, Transform transform)
{
    auto model = std::make_shared<FBXModel>(filePath,transform);
    sceneModels.push_back(model);
    return sceneModels.back();
}

std::shared_ptr<FBXModel> Model3DManager::CreateChildFBXModel(std::shared_ptr<FBXModel> parent, const char* filePath)
{
    std::shared_ptr<FBXModel> child = nullptr;
    if (parent != nullptr)
    {
        // Create a shared_ptr to the new child model
        auto childModel = std::make_shared<FBXModel>(filePath);

        sceneModels.push_back(childModel);  // Add the shared pointer to the vector

        // Set parent and establish the relationship
        parent->children.push_back(childModel);
        childModel->parent = parent;

        child = childModel;  // Return the shared pointer
    }

    return child;
}

std::shared_ptr<FBXModel> Model3DManager::CreateChildFBXModel(std::shared_ptr<FBXModel> parent, const char* filePath, Transform transform)
{
    std::shared_ptr<FBXModel> child = nullptr;
    if (parent != nullptr)
    {
        // Create a shared_ptr to the new child model
        auto childModel = std::make_shared<FBXModel>(filePath);

        sceneModels.push_back(childModel);  // Add the shared pointer to the vector

        // Set parent and establish the relationship
        parent->children.push_back(childModel);
        childModel->parent = parent;
        childModel->transform = transform;
        child = childModel;  // Return the shared pointer
    }

    return child;
}


void Model3DManager::DrawFBXModel(const std::shared_ptr<FBXModel> model)
{
    
    //	for every polygons in the model
    for (const auto& polygon : model->polygons)
    {
        glBegin(GL_POLYGON);

        //glColor3d(polygon.color.r, polygon.color.g,polygon.color.b);

        //	for every vertices in the polygon
        for(const auto& vertex : polygon.vertices)
        {
            auto uv = vertex.uv;
            double uvX = static_cast<double>(uv.mData[0]);
            double uvY = static_cast<double>(uv.mData[1]);

            auto normal = vertex.normal;
            double nX = static_cast<double>(normal.mData[0]);
            double nY = static_cast<double>(normal.mData[1]);
            double nZ = static_cast<double>(normal.mData[2]);

            auto position = vertex.position;
            double x = static_cast<double>(position.mData[0]); 
            double y = static_cast<double>(position.mData[1]); 
            double z = static_cast<double>(position.mData[2]); 
		
            glTexCoord2d(uvX, uvY);
            glNormal3d(nX,nY,nZ);
            glVertex3d(x,y,z);
        }
		
        glEnd();
    }
    

}

void Model3DManager::DrawFBXModelWithTransform(const std::shared_ptr<FBXModel> model)
{
    auto pos = model->transform.position;
    auto rotation = model->transform.rotation;
    auto scale = model->transform.scale;

    glPushMatrix();
    glTranslated(pos.x, pos.y, pos.z);
    glRotated(rotation.x,1,0,0);
    glRotated(rotation.y,0,1,0);
    glRotated(rotation.z,0,0,1);
    glScaled(scale.x, scale.y,scale.z);
    
    //draw model
    if(model->isActive)
        DrawFBXModel(model);

    //draw children models (recursive)
    if(!model->children.empty())
        for(auto child : model->children)
        {
            DrawFBXModelWithTransform(child);
        }

    glPopMatrix();
    
}


