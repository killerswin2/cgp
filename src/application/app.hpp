#pragma once
#include <iostream>
#include <string>
#include <stack>
#include <cmath>
#include <sstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../debug/messageDebugger.h"
#include "../shader/shader.h"
#include "../model/model.hpp"

#define numVAOs 1
#define numVBOs 2

class Application
{
private:
    glm::vec3 m_CameraPos;
    glm::vec3 m_PyramPos;
    GLuint m_VAO[numVAOs];
    GLuint m_VBO[numVBOs];

    std::stack<glm::mat4> m_MVStack;
    int m_Width;
    int m_Height;
    float m_aspect;
    glm::mat4 m_PMat;
    glm::mat4 m_VMat;
    glm::mat4 m_MMat;
    glm::mat4 m_MVMat;

    GLFWwindow* m_Window;

    double m_CurrentTime;
    Shader m_Shader;
    Model m_Model;

    void setUpVertices(void);
    void init(void);
    void display();

public:
    Application();
    static void window_reshape_callback(GLFWwindow* window, int newWidth, int newHeight);
    void run();
};