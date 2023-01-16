#ifndef __GL_PROGRAM_H
#define __GL_PROGRAM_H
#include <gl/glew.h>
#include <vector>
#include "../shader/shader.h"
#include "../debug/messageDebugger.h"

class program
{
    private:
        GLuint m_program;
        std::vector<shader> m_shaders;

    public:
        program(){GLCall(m_program = glCreateProgram());};
        void linkProgram();
        void pushBackShader(shader glShader);
        void attachShaders();
        GLuint getGLProgram() {return m_program;}

};
#endif