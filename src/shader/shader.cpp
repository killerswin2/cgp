#include "shader.h"


shader::shader(std::filesystem::path filepath, GLenum shaderType) : m_filePath{filepath}, m_shaderType{shaderType}
{
    createShader();
}
void shader::createShader()
{
    GLCall(m_shader = glCreateShader(m_shaderType));

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
    glShaderSource(m_shader, 1, &shaderCharData , NULL);
    glCompileShader(m_shader);

    int result;
    glGetShaderiv(m_shader, GL_COMPILE_STATUS, &result);

    if(result == GL_FALSE)
    {
        printShaderLog(m_shader);
    }   
}

const char* shader::shaderData()
{
    return m_shaderData.data();
}

GLuint shader::getShader()
{
    return m_shader;
}