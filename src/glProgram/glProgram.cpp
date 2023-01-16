#include "glProgram.h"
#include <iostream>

void program::linkProgram()
{
    // link and check link for success
    GLint result;
    GLCall(glLinkProgram(m_program));
    glGetProgramiv(m_program, GL_LINK_STATUS, &result);

    if (result == GL_FALSE)
    {
        printProgramLog(m_program);
    }

    // validate the program before we try to run it
    result = GL_TRUE;
    GLCall(glValidateProgram(m_program)); // check to see if the shaders can execute in the opengl state.
    glGetProgramiv(m_program, GL_VALIDATE_STATUS, &result);

    if(result == GL_FALSE)
    {
        printProgramLog(m_program);
    }
    
    // free the memory on the gpu?
    deleteShaders();
}

void program::pushBackShader(shader glShader)
{
    m_shaders.push_back(glShader);
}

void program::attachShaders()
{
    for(int i = 0; i < m_shaders.size(); i++)
    {
        GLCall(glAttachShader(m_program, m_shaders[i].getShader()));
    }
    linkProgram();
}

void program::deleteShaders()
{
    // delete all the shaders
    GLsizei maxCount = 20;
    GLsizei count;
    GLuint shaders[20];
    GLCall(glGetAttachedShaders(m_program, maxCount, &count, shaders));

    // we don't need to do anything else
    if(count == 0)
    {
        return;
    } 
    else 
    {
        for(int i = 0; i < count; i++)
        {
            // delete shader
            GLCall(glDeleteShader(shaders[i]));
        }
    }
}