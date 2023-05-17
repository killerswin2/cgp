#include "shader.h"


shader::shader(const std::filesystem::path& vertexPath, const std::filesystem::path& fragmentPath)
{
    GLuint vertexShader, fragmentShader;
    GLCall(vertexShader = glCreateShader(GL_VERTEX_SHADER));
    GLCall(fragmentShader = glCreateShader(GL_FRAGMENT_SHADER));
    

    std::ifstream vertexFile;
    std::ifstream fragmentFile;
    std::string vertexShaderString;
    std::string fragmentShaderString;

    // ifstream objects can throw execptions
    vertexFile.exceptions(std::ifstream::badbit);
    fragmentFile.exceptions(std::ifstream::badbit);

    //open and do file stuff
    try
    {
        vertexFile.open(vertexPath);
        fragmentFile.open(fragmentPath);
        std::ostringstream vertextStream, fragmentStream;

        // vertext
        vertextStream << vertexFile.rdbuf();
        vertexShaderString = vertextStream.str();

        // fragment
        fragmentStream << fragmentFile.rdbuf();
        fragmentShaderString = fragmentStream.str();

        // close files
        vertexFile.close();
        fragmentFile.close();

    }
    catch (std::ifstream::failure error)
    {
        std::cout << "ERROR SHADER FILE NOT READ\n"; 
    }


    // set shader source and compile
    const char* vertextCharData = vertexShaderString.data();
    const char* fragmentCharData = fragmentShaderString.data();
    glShaderSource(vertexShader, 1, &vertextCharData , NULL);
    glShaderSource(fragmentShader, 1, &fragmentCharData , NULL);
    glCompileShader(vertexShader);
    glCompileShader(fragmentShader);

    // check the the shaders compiled right
    GLint result;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);

    if(result == GL_FALSE)
    {
        printShaderLog(vertexShader);
        GLCall(glDeleteShader(vertexShader));
    } 

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);

    if(result == GL_FALSE)
    {
        printShaderLog(fragmentShader);
        GLCall(glDeleteShader(fragmentShader));
    } 

    // create and attach shaders to program
    GLCall(m_glProgram = glCreateProgram());
    GLCall(glAttachShader(m_glProgram, vertexShader));
    GLCall(glAttachShader(m_glProgram, fragmentShader));

    // link program and check for success
    GLCall(glLinkProgram(m_glProgram));
    GLCall(glGetProgramiv(m_glProgram, GL_LINK_STATUS, &result));

    if (result == GL_FALSE)
    {
        printProgramLog(m_glProgram);
    }

    // validate the program before we try to run it
    result = GL_TRUE;
    GLCall(glValidateProgram(m_glProgram)); // check to see if the shaders can execute in the opengl state.
    glGetProgramiv(m_glProgram, GL_VALIDATE_STATUS, &result);

    if(result == GL_FALSE)
    {
        printProgramLog(m_glProgram);
    }
    
    // free the memory on the gpu
    GLCall(glDeleteShader(vertexShader));
    GLCall(glDeleteShader(fragmentShader));
}

GLuint shader::getGLProgram() 
{
    return m_glProgram;
}

void shader::useProgram() 
{
    GLCall(glUseProgram(m_glProgram));
}

GLint shader::getUniformLocation(const GLchar* name)
{
    GLint loc;
    GLCall(loc = glGetUniformLocation(m_glProgram, name));
    return loc;
}

void shader::setUniform1f(const GLchar* name, float value) {}

void shader::setUniform1fv(const GLchar* name, float* value, GLsizei count) {}

void shader::setUniform1i(const GLchar* name, int value) {}

void shader::setUniform1ui(const GLchar* name, unsigned int value) {}

void shader::setUniform1iv(const GLchar* name, int* value, GLsizei count) {}

void shader::setUniform2f(const GLchar* name, const glm::vec2& vector) {}

void shader::setUniform3f(const GLchar* name, const glm::vec3& vector) {}

void shader::setUniform4f(const GLchar* name, const glm::vec4& vector) {}

void shader::setUniformMat4f(const char* name, const glm::mat4& value) 
{
        GLCall(glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value)));
}