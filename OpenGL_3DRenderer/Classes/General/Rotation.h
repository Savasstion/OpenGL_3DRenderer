#pragma once

struct Rotation
{
    double x = 0, y = 0, z = 0;   // 0 to 360

    Rotation(const double x,const double y,const double z)
        : x(x), y(y), z(z) {}
    Rotation(const double xyz)
        : x(xyz), y(xyz), z(xyz) {}
    Rotation(){ x = y = z = 0;}
};
