#include <iostream>
#include <string>
#include <cmath>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "debug/messageDebugger.h"
#include "shader/shader.h"


#define numVAOs 1
#define numVBOs 2

//gl stuff

static float cameraX, cameraY, cameraZ;
static float cubePosX, cubePosY, cubePosZ;
static float pyramPosX, pyramPosY, pyramPosZ;

GLuint vao[numVAOs];
GLuint vbo[numVBOs];

// animation helpers

static float xPos = 0.0f;
static float posInc = 0.5f;

// timers

static double frameTimeLast = 0.0;

// display helpers

static int width, height;
static float aspect;
static glm::mat4 pMat, vMat, mMat, mvMat;


/**
 * @brief Creates and binds vertex data.
 * 
 * @return GLuint 
 */
void setUpVertices(void)
{
    float vertexPositions[108] = {
        -1.0, -1.0, 1.0, 1.0, -1.0, 1.0, 1.0, 1.0, 1.0,
        -1.0, -1.0, 1.0, 1.0, 1.0, 1.0, -1.0, 1.0, 1.0,
        1.0, -1.0, 1.0, 1.0, -1.0, -1.0, 1.0, 1.0, -1.0,
        1.0, -1.0, 1.0, 1.0, 1.0, -1.0, 1.0, 1.0, 1.0,
        1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, 1.0, -1.0,
        1.0, -1.0, -1.0, -1.0, 1.0, -1.0, 1.0, 1.0, -1.0,
        -1.0, -1.0, -1.0, -1.0, -1.0, 1.0, -1.0, 1.0, 1.0,
        -1.0, -1.0, -1.0, -1.0, 1.0, 1.0, -1.0, 1.0, -1.0,
        -1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, -1.0,
        -1.0, 1.0, 1.0, 1.0, 1.0, -1.0, -1.0, 1.0, -1.0,
        1.0, -1.0, 1.0, -1.0, -1.0, -1.0, 1.0, -1.0, -1.0,
        1.0, -1.0, 1.0, -1.0, -1.0, 1.0, -1.0, -1.0, -1.0
    };

    float pyramidPositions[54] =
    {
        -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f,
        1.0f, -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f
    };

    GLCall(glGenVertexArrays(numVAOs, vao));
    GLCall(glBindVertexArray(vao[0]));
    GLCall(glGenBuffers(numVBOs, vbo));

    GLCall(glBindBuffer(GL_ARRAY_BUFFER, vbo[0]));
    GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW));

    GLCall(glBindBuffer(GL_ARRAY_BUFFER, vbo[1]));
    GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(pyramidPositions), pyramidPositions, GL_STATIC_DRAW));

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
    cameraX = 0.0f;
    cameraY = 0.0f;
    cameraZ = 10.0f;

    cubePosX = 0.0f;
    cubePosY = -2.0f;
    cubePosZ = 0.0f;

    pyramPosX = 0.0f;
    pyramPosY = 2.0f;
    pyramPosZ = 0.0f;
    setUpVertices();

};

/**
 * @brief render function
 * 
 * This function repeated draws the info to screen. 
 * 
 * @param window glfw window with opengl context
 * @param currentTime time since window init
 */
void display(GLFWwindow* window, double currentTime, shader& Shader)
{
    GLuint renderingProgram = Shader.getGLProgram();
    // calculate deltaTime;
    double deltaTime = currentTime - frameTimeLast;     // (final - init)
    frameTimeLast = currentTime;


    GLCall(glClear(GL_DEPTH_BUFFER_BIT));
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
    Shader.useProgram();



    //build perspective matrix
    glfwGetFramebufferSize(window, &height, &width);
    aspect = (float) width / (float) height;
    pMat = glm::perspective(1.0472f, aspect, 0.1f, 1000.0f);


    // model, view and model-view matrix
    vMat = glm::translate(glm::mat4(1.0f), glm::vec3(-cameraX, -cameraY, -cameraZ));
    mMat = glm::translate(glm::mat4(1.0f), glm::vec3(cubePosX, cubePosY, cubePosZ));
    mvMat = vMat * mMat;

    // copyPerspective and MV matrices to uniforms
    Shader.setUniformMat4f("mv_matrix", mvMat);
    Shader.setUniformMat4f("proj_matrix", pMat);


    // associate VBO with vertex attribute in shader
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, vbo[0]));
    GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0));
    GLCall(glEnableVertexAttribArray(0));

    // adjust opengl settings
    GLCall(glEnable(GL_DEPTH_TEST));
    GLCall(glDepthFunc(GL_LEQUAL));
    GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));

    //pyramid 
    mMat = glm::translate(glm::mat4(1.0f), glm::vec3(pyramPosX, pyramPosY, pyramPosZ));
    mvMat = vMat * mMat;

    // copyPerspective and MV matrices to uniforms
    Shader.setUniformMat4f("mv_matrix", mvMat);
    Shader.setUniformMat4f("proj_matrix", pMat);

    // associate VBO with vertex attribute in shader
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, vbo[1]));
    GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0));
    GLCall(glEnableVertexAttribArray(0));

    // adjust opengl settings
    GLCall(glEnable(GL_DEPTH_TEST));
    GLCall(glDepthFunc(GL_LEQUAL));
    GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));

}

int main()
{

    // init glfw
    if(!glfwInit()) {exit(EXIT_FAILURE);}

    //opengl contexts
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    //make window
    GLFWwindow* window = glfwCreateWindow(600, 600, "Opengl Stuff Window", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    //init glew
    if(glewInit() != GLEW_OK) {exit(EXIT_FAILURE);}


    GLCall(glEnable(GL_DEBUG_OUTPUT));
    GLCall(glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS));
    GLCall(glDebugMessageCallback(debugMessageCallback, nullptr));

    //turn of v-sync
    glfwSwapInterval(1);

    init(window);

    // shader thing.
    shader Shader{"shaders/vertexShaderSimple.glsl", "shaders/fragmentShaderSimple.glsl"};


    // handle exit code
    while(!glfwWindowShouldClose(window)) 
    {
        display(window, glfwGetTime(), Shader);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // termination code
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}