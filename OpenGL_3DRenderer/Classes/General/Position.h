#pragma once
#define fbxToOpenGLPos 1.0 / 6

struct Position
{
    double x = 0, y = 0, z = 0;
    bool toConvertFromFBXToOpenGL = false;

    Position(const double x,const double y,const double z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    Position(const double x,const double y,const double z, const bool toConvertFromFBXToOpenGL)
    {
        this->x = x * (fbxToOpenGLPos * toConvertFromFBXToOpenGL);
        this->y = y * (fbxToOpenGLPos * toConvertFromFBXToOpenGL);
        this->z = z * (fbxToOpenGLPos * toConvertFromFBXToOpenGL);
    }

    Position(const double xyz, const bool toConvertFromFBXToOpenGL)
    {
        this->x = xyz * (fbxToOpenGLPos * toConvertFromFBXToOpenGL);
        this->y = xyz * (fbxToOpenGLPos * toConvertFromFBXToOpenGL);
        this->z = xyz * (fbxToOpenGLPos * toConvertFromFBXToOpenGL);
    }
    
    Position(const double xyz)
    {
        this->x = xyz ;
        this->y = xyz ;
        this->z = xyz ;
    }
    
    Position(){ x = y = z = 0.0;}
};
