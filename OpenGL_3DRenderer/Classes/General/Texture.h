#pragma once
#include <Windows.h>
#include <gl/GL.h>

class Texture
{
public:
    GLuint texture = 0;	// texture name
    BITMAP BMP;			// bitmap structure
    HBITMAP hBMP;		// bitmap handle
    bool isConfigured = false;

    Texture(LPCSTR fileName);
    GLuint ConfigureTexture();
    void ClearTexture();
};
