#ifndef __MESSAGE_DEBUGGER_H
#define __MESSAGE_DEBUGGER_H

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

bool checkOpenGLError();
void printProgramLog(GLuint program);
void printShaderLog(GLuint shader);
void APIENTRY debugMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *msg, const void *data);

#endif