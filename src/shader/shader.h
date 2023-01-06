#ifndef __SHADER__H
#define __SHADER__H

#include <GL/glew.h>
#include <string>
#include <filesystem>
#include <iostream>
#include <sstream>
#include <fstream>
#include "../debug/messageDebugger.h"

class shader
{
    private:
        GLuint m_shader;
        std::string m_shaderData;
        std::filesystem::path m_filePath;
        GLenum m_shaderType;
    public:
        shader(std::filesystem::path filepath, GLenum shaderType);
        void createShader();
        const char* shaderData();
        GLuint getShader();

};

#endif