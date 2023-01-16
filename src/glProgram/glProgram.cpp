#include "glProgram.h"
#include <iostream>

void program::linkProgram(){
    GLCall(glLinkProgram(m_program));
    printProgramLog(m_program);
    GLCall(glValidateProgram(m_program)); // check to see if the shaders can execute in the opengl state.
    printProgramLog(m_program);
}
void program::pushBackShader(shader glShader){
    m_shaders.push_back(glShader);
}
void program::attachShaders(){
    for(int i = 0; i < m_shaders.size(); i++)
    {
        GLCall(glAttachShader(m_program, m_shaders[i].getShader()));
    }
    linkProgram();
}