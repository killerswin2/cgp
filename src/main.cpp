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
#include "glProgram/glProgram.h"


#define numVAOs 1
#define numVBOs 2

//gl stuff

float cameraX, cameraY, cameraZ;
float cubePosX, cubePosY, cubePosZ;

GLuint renderingProgram;
GLuint vao[numVAOs];
GLuint vbo[numVBOs];

// animation helpers

static float xPos = 0.0f;
static float posInc = 0.5f;

// timers

static double frameTimeLast = 0.0;

// display helpers

GLuint mvLoc, projLoc;
int width, height;
float aspect;
glm::mat4 pMat, vMat, mMat, mvMat, tMat, rMat;


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

    GLCall(glGenVertexArrays(1, vao));
    GLCall(glBindVertexArray(vao[0]));
    GLCall(glGenBuffers(numVBOs, vbo));

    GLCall(glBindBuffer(GL_ARRAY_BUFFER, vbo[0]));
    GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW));

}



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
    cameraX = 0.0f;
    cameraY = 0.0f;
    cameraZ = 8.0f;

    cubePosX = 0.0f;
    cubePosY = -2.0f;
    cubePosZ = 0.0f;
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
void display(GLFWwindow* window, double currentTime)
{
    // calculate deltaTime;

    double deltaTime = currentTime - frameTimeLast;     // (final - init)
    frameTimeLast = currentTime;


    GLCall(glClear(GL_DEPTH_BUFFER_BIT));
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
    GLCall(glUseProgram(renderingProgram));

    // get uniform locations
    GLCall(mvLoc = glGetUniformLocation(renderingProgram, "mv_matrix"));
    GLCall(projLoc = glGetUniformLocation(renderingProgram, "proj_matrix"));

    //build perspective matrix
    glfwGetFramebufferSize(window, &height, &width);
    aspect = (float) width / (float) height;
    pMat = glm::perspective(1.0472f, aspect, 0.1f, 1000.0f);

    // model, view and model-view matrix
    vMat = glm::translate(glm::mat4(1.0f), glm::vec3(-cameraX, -cameraY, -cameraZ));
    mMat = glm::translate(glm::mat4(1.0f), glm::vec3(cubePosX, cubePosY, cubePosZ));

    //rotation and movement
    tMat = glm::translate(glm::mat4(1.0f), glm::vec3(sin(0.35f * currentTime)* 2.0f, cos(0.52f * currentTime) * 2.0f, sin(0.7 * currentTime) * 2.0f));
    rMat = glm::rotate(glm::mat4(1.0f), 1.75f * (float)currentTime, glm::vec3(0.0f, 1.0f, 0.0f));
    rMat = glm::rotate(rMat,1.75f * (float)currentTime, glm::vec3(1.0f, 0.0f, 0.0f));
    rMat = glm::rotate(rMat,1.75f * (float)currentTime, glm::vec3(0.0f, 0.0f, 1.0f));
    mMat = tMat * rMat;
    mvMat = vMat * mMat;

    // copyPerspective and MV matrices to uniforms
    GLCall(glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMat)));
    GLCall(glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat)));

    // associate VBO with vertex attribute in shader
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, vbo[0]));
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