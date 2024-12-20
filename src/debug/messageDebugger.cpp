#include "messageDebugger.h"


void APIENTRY debugMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *msg, const void *data)
{
    std::string _source;
    std::string _type;
    std::string _severity;

    switch (source) {
        case GL_DEBUG_SOURCE_API:
        _source = "API";
        break;

        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
        _source = "WINDOW SYSTEM";
        break;

        case GL_DEBUG_SOURCE_SHADER_COMPILER:
        _source = "SHADER COMPILER";
        break;

        case GL_DEBUG_SOURCE_THIRD_PARTY:
        _source = "THIRD PARTY";
        break;

        case GL_DEBUG_SOURCE_APPLICATION:
        _source = "APPLICATION";
        break;

        case GL_DEBUG_SOURCE_OTHER:
        _source = "UNKNOWN";
        break;

        default:
        _source = "UNKNOWN";
        break;
    }

    switch (type) {
        case GL_DEBUG_TYPE_ERROR:
        _type = "ERROR";
        break;

        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
        _type = "DEPRECATED BEHAVIOR";
        break;

        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
        _type = "UDEFINED BEHAVIOR";
        break;

        case GL_DEBUG_TYPE_PORTABILITY:
        _type = "PORTABILITY";
        break;

        case GL_DEBUG_TYPE_PERFORMANCE:
        _type = "PERFORMANCE";
        break;

        case GL_DEBUG_TYPE_OTHER:
        _type = "OTHER";
        break;

        case GL_DEBUG_TYPE_MARKER:
        _type = "MARKER";
        break;

        default:
        _type = "UNKNOWN";
        break;
    }

    switch (severity) {
        case GL_DEBUG_SEVERITY_HIGH:
        _severity = "HIGH";
        break;

        case GL_DEBUG_SEVERITY_MEDIUM:
        _severity = "MEDIUM";
        break;

        case GL_DEBUG_SEVERITY_LOW:
        _severity = "LOW";
        break;

        case GL_DEBUG_SEVERITY_NOTIFICATION:
        _severity = "NOTIFICATION";
        break;

        default:
        _severity = "UNKNOWN";
        break;
    }

    printf("%d: %s of %s severity, raised from %s: %s\n",
            id, _type.c_str(), _severity.c_str(), _source.c_str(), msg);
}


void printShaderLog(GLuint shader)
{
    GLint shaderType = 0;
    GLCall(glGetShaderiv(shader, GL_SHADER_TYPE, &shaderType));
    std::string shaderTypeName;

    switch (shaderType)
    {
        case GL_VERTEX_SHADER:
        {
            shaderTypeName = std::string{"Vertex Shader\n"};
        }
        break;

        case GL_GEOMETRY_SHADER :
        {
            shaderTypeName = std::string{"Geometry Shader\n"};
        }

        case GL_FRAGMENT_SHADER  :
        {
            shaderTypeName = std::string{"Fragment Shader\n"};
        }
        break;
    default:
        break;
    }


    std::cerr << "Type of Shader: " << shaderTypeName << "\n";
    int length = 0;
    int chWrittenToLog = 0;
    char *log;
    GLCall(glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length));
    if (length > 0 ) 
    {
        log = new char[length];
        GLCall(glGetShaderInfoLog(shader, length, &chWrittenToLog, log));
        std::cerr << "Shader Info log: " << log << "\n";
        delete log;
    }
}

void printProgramLog(GLuint program) 
{
    int length = 0;
    int chWrittenToLog = 0;
    char *log;
    GLCall(glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length));
    if(length > 0)
    {
        log = new char[length];
        GLCall(glGetProgramInfoLog(program, length, &chWrittenToLog, log));
        std::cerr << "Program Info log: " << log << "\n";
        delete log;
    }

}

bool checkOpenGLError()
{
    bool foundError = false;
    int glError = glGetError();
    while(glError != GL_NO_ERROR)
    {
        std::cerr << "glError: " << glError << "\n";
        foundError = true;
        glError = glGetError();
    }
    return foundError;
}

void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        std::cerr << " [OpenGL_Error] (" << error << ") " << function <<
            " " << file << ":" << line << std::endl;
        return false;
    }
    return true;
}