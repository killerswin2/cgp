#include "shader.h"


shader::shader(std::filesystem::path filepath, GLenum shaderType) : m_filePath{filepath}, m_shaderType{shaderType}
{
    createShader();
}
void shader::createShader()
{
    //if (checkOpenGLError()) {std::cerr << "before shader create\n";printShaderLog(m_shader);}
    m_shader = glCreateShader(m_shaderType);
    //if (checkOpenGLError()) {std::cerr << "After shader create\n";printShaderLog(m_shader);}

    std::ifstream in(m_filePath);
    std::string shader{};
    if(in) 
    {
        std::ostringstream ss;
        ss << in.rdbuf();
        shader = ss.str();
    }
    m_shaderData = shader;
    const char* shaderCharData = shader.data();
    //if (checkOpenGLError()) {std::cerr << "Before shader source\n";printShaderLog(m_shader);}
    glShaderSource(m_shader, 1, &shaderCharData , NULL);
    //if (checkOpenGLError()) {std::cerr << "After shader source\n";printShaderLog(m_shader);}
    glCompileShader(m_shader);
    //if (checkOpenGLError()) {std::cerr << "After shader compile\n";printShaderLog(m_shader);}
}

const char* shader::shaderData()
{
    return m_shaderData.data();
}

GLuint shader::getShader()
{
    return m_shader;
}