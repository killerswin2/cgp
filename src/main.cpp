#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include "debug/messageDebugger.h"
#include "shader/shader.h"
#include "glProgram/glProgram.h"


#define numVAOs 1

GLuint renderingProgram;
GLuint vao[numVAOs]; 


GLuint createShaderProgram() 
{
    GLuint vShaderCompiled;
    GLuint fShaderCompiled;
    GLuint shaderLinked;

    shader vShader{"shaders/vertexShaderSimple.glsl", GL_VERTEX_SHADER};
    shader fShader{"shaders/fragmentShaderSimple.glsl", GL_FRAGMENT_SHADER};

    //const char * vShaderChar = vShaderSource.data();
    //const char * fShaderChar = fShaderSource.data();

    //GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
    //GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);


    //GLuint vfProgram = glCreateProgram();
    //glAttachShader(vfProgram, vShader.getShader());
    //glAttachShader(vfProgram, fShader.getShader());
    //glLinkProgram(vfProgram);

    program glProgram;
    glProgram.pushBackShader(vShader);
    glProgram.pushBackShader(fShader);
    glProgram.attachShaders();

    GLuint vfProgram = glProgram.getGLProgram();
    return vfProgram;

}

void init(GLFWwindow* window) 
{
    renderingProgram = createShaderProgram();
    glGenVertexArrays(numVAOs, vao);
    glBindVertexArray(vao[0]);

};

void display(GLFWwindow* window, double currentTime)
{
    glUseProgram(renderingProgram);
    glPointSize(30.0f);
    glDrawArrays(GL_POINTS, 0, 1);
}

int main()
{

    // init glfw
    if(!glfwInit()) {exit(EXIT_FAILURE);}

    //opengl contexts
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    //make window
    GLFWwindow* window = glfwCreateWindow(600, 600, "Chapter2 - program1", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    //init glew
    if(glewInit() != GLEW_OK) {exit(EXIT_FAILURE);}


    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(debugMessageCallback, nullptr);

    //turn of v-sync
    glfwSwapInterval(1);

    init(window);

    // handle exit code
    while(!glfwWindowShouldClose(window)) 
    {
        display(window, glfwGetTime());
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // termination code
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);

}