#include "glProgram.h"
#include <iostream>

void program::linkProgram(){
    glLinkProgram(m_program);
}
void program::pushBackShader(shader glShader){
    m_shaders.push_back(glShader);
}
void program::attachShaders(){
    for(int i = 0; i < m_shaders.size(); i++)
    {
        glAttachShader(m_program, m_shaders[i].getShader());
    }
    linkProgram();
}