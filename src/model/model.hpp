#pragma once

#include <GL/glew.h>
#include <string>
#include <iostream>
#include <filesystem>
#include <SOIL2/SOIL2.h>

class Model
{
private:
    GLuint m_TextureID;
public:
    Model();
    void loadTextureFromFile(const char *path);
    GLuint getTextureID(){ return m_TextureID;}
};