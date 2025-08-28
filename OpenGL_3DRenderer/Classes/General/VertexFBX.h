#pragma once
#include <fbxsdk.h>

struct VertexFBX
{
    FbxVector4 position;
    FbxVector4 normal;
    FbxVector2 uv;

    VertexFBX(const FbxVector4& pos, const FbxVector4& norm, const FbxVector2& texCoord)
        : position(pos), normal(norm), uv(texCoord) {}
};
