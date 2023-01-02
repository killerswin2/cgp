#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define numVAOs 1

GLuint renderingProgram;
GLuint vao[numVAOs];

GLuint createShaderProgram() 
{
    const char* vShaderSource =
        "#version 430 \n"
        "void main(void) \n"
        "{gl_Position = vec4(0.0, 0.0, 0.0, 1.0);}";

    const char* fShaderSource = 
        "#version 430 \n"
        "out vec4 color; \n"
        "void main(void) \n"
        "{color = vec4(0.0, 0.0, 1.0, 1.0);}";

    GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vShader, 1, &vShaderSource, NULL);
    glShaderSource(fShader, 1, &fShaderSource, NULL);
    glCompileShader(vShader);
    glCompileShader(fShader);

    GLuint vfProgram = glCreateProgram();
    glAttachShader(vfProgram, vShader);
    glAttachShader(vfProgram, fShader);
    glLinkProgram(vfProgram);

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