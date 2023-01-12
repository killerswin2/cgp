#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "debug/messageDebugger.h"
#include "shader/shader.h"
#include "glProgram/glProgram.h"


#define numVAOs 1

//gl stuff

GLuint renderingProgram;
GLuint vao[numVAOs];

// animation helpers

static float xPos = 0.0f;
static float posInc = 0.5f;

// timers

static double frameTimeLast = 0.0;

/**
 * @brief Create a Shader Program object
 * 
 * @return GLuint 
 */
GLuint createShaderProgram() 
{
    shader vShader{"shaders/vertexShaderSimple.glsl", GL_VERTEX_SHADER};
    shader fShader{"shaders/fragmentShaderSimple.glsl", GL_FRAGMENT_SHADER};

    program glProgram;
    glProgram.pushBackShader(vShader);
    glProgram.pushBackShader(fShader);
    glProgram.attachShaders();

    GLuint vfProgram = glProgram.getGLProgram();
    return vfProgram;

}

/**
 * @brief opengl "init" function
 * 
 * This function creates the rendering program from opengl 
 * and generates and binds the vertexArrays
 * 
 * @param window pointer to glfw windows that has the opengl context
 */
void init(GLFWwindow* window) 
{
    renderingProgram = createShaderProgram();
    glGenVertexArrays(numVAOs, vao);
    glBindVertexArray(vao[0]);

};

/**
 * @brief render function
 * 
 * This function repeated draws the info to screen. 
 * 
 * @param window glfw window with opengl context
 * @param currentTime time since window init
 */
void display(GLFWwindow* window, double currentTime)
{
    // calculate deltaTime;

    double deltaTime = currentTime - frameTimeLast;     // (final - init)
    frameTimeLast = currentTime;


    glClear(GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0, 0.0,0.0,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(renderingProgram);

    xPos += (posInc * deltaTime);
    if (xPos > 1.0f) 
    {
        posInc = -0.5f;
    }
    if (xPos < -1.0f) 
    {
        posInc = 0.5f;
    }

    //uniforms
    GLuint offsetLocation = glGetUniformLocation(renderingProgram, "offset");
    glProgramUniform1f(renderingProgram, offsetLocation, xPos);

    glDrawArrays(GL_TRIANGLES, 0, 3);
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