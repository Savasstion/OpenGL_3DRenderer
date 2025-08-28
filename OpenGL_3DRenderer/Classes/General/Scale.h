#pragma once

struct Scale
{
    double x = 1, y = 1, z = 1;

    Scale(const double x,const double y,const double z)
        : x(x), y(y), z(z) {}
    Scale(const double xyz)
        : x(xyz), y(xyz), z(xyz) {}
    Scale(){ x = y = z = 1.0;}
};
