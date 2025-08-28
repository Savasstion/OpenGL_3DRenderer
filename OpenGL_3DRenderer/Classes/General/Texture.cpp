#include "Texture.h"

Texture::Texture(LPCSTR fileName)
{
    // Initialize texture info
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
    HBITMAP hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
        fileName, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
        LR_LOADFROMFILE);
    GetObject(hBMP, sizeof(BMP), &BMP);
}

GLuint Texture::ConfigureTexture()
{
    if(!isConfigured)
    {
        // Enable and Configure/Create the texture
        glEnable(GL_TEXTURE_2D);
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
            BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

        isConfigured = true; 
    }
    else
    {
        glBindTexture(GL_TEXTURE_2D, texture);
    }
    
    return texture;
}

void Texture::ClearTexture()
{
    glDisable(GL_TEXTURE_2D);
    DeleteObject(hBMP);
    glDeleteTextures(1, &texture);
    isConfigured = false;
}
