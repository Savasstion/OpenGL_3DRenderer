#pragma once
#include "Position.h"
#include "Rotation.h"
#include "Scale.h"

struct Transform
{
    bool isActive = true;   //for now, just used to check if this transform should be used
    Position position;
    Rotation rotation;
    Scale scale;

    Transform(const Position position,const Rotation rotation,const Scale scale)
        : position(position), rotation(rotation), scale(scale) {}
    Transform()
        : position(Position()), rotation(Rotation()), scale(Scale()) {}
};
