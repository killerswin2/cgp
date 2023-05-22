#ifndef __SHADER__H
#define __SHADER__H

#include <GL/glew.h>
#include <string>
#include <filesystem>
#include <iostream>
#include <sstream>
#include <fstream>
#include "../debug/messageDebugger.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

/**
 * @brief Abstraction of opengl shader
 * 
 * This class abstracts away most of the opengl shader functions needed for basic creation.
 * Creates and compiles shaders for later use with program
 */
class Shader
{
    private:
        GLuint m_glProgram;

        GLint getUniformLocation(const std::string& name);
    public:
        Shader(){};
        Shader(const std::filesystem::path& vertexPath, const std::filesystem::path& fragmentPath);
        GLuint getGLProgram();
        void useProgram();
        GLint getUniformLocation(const GLchar* name);
        void setUniform1f(const GLchar* name, float value);
        void setUniform1fv(const GLchar* name, float* value, GLsizei count);
        void setUniform1i(const GLchar* name, int value);
        void setUniform1ui(const GLchar* name, unsigned int value);
        void setUniform1iv(const GLchar* name, int* value, GLsizei count);
        void setUniform2f(const GLchar* name, const glm::vec2& vector);
        void setUniform3f(const GLchar* name, const glm::vec3& vector);
        void setUniform4f(const GLchar* name, const glm::vec4& vector);
        void setUniformMat4f(const char* name, const glm::mat4& value);


};

#endif