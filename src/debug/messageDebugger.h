#ifndef __MESSAGE_DEBUGGER_H
#define __MESSAGE_DEBUGGER_H

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#if __linux__
#include <unistd.h>
#include <signal.h>
#ifdef _DEBUG_BUILD
#define ASSERT(x) if(!(x)) raise(SIGTRAP)
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))
#else
#define ASSERT(x) if(!(x)) raise(SIGTRAP)
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))
#endif
#else
// windows
#if _DEBUG
#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))
#else
// don't do error checking in release builds for opengl
#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) \
    x;
#endif
#endif

bool checkOpenGLError();
void printProgramLog(GLuint program);
void printShaderLog(GLuint shader);
void APIENTRY debugMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *msg, const void *data);
void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

#endif