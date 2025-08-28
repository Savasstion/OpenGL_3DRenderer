#pragma once
#include <vector>

#include "Color.h"
#include "VertexFBX.h"

struct PolygonFBX
{
    std::vector<VertexFBX> vertices;
    Color color;

    PolygonFBX(const std::vector<VertexFBX> vertices, const Color color)
        : vertices(vertices), color(color) {}
};
