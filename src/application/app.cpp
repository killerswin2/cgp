#include "app.hpp"

/**
 * @brief Creates and binds vertex data.
 * 
 * @return GLuint 
 */
void Application::setUpVertices(void)
{
    // float vertexPositions[108] = {
    //     -1.0, -1.0, 1.0, 1.0, -1.0, 1.0, 1.0, 1.0, 1.0,
    //     -1.0, -1.0, 1.0, 1.0, 1.0, 1.0, -1.0, 1.0, 1.0,
    //     1.0, -1.0, 1.0, 1.0, -1.0, -1.0, 1.0, 1.0, -1.0,
    //     1.0, -1.0, 1.0, 1.0, 1.0, -1.0, 1.0, 1.0, 1.0,
    //     1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, 1.0, -1.0,
    //     1.0, -1.0, -1.0, -1.0, 1.0, -1.0, 1.0, 1.0, -1.0,
    //     -1.0, -1.0, -1.0, -1.0, -1.0, 1.0, -1.0, 1.0, 1.0,
    //     -1.0, -1.0, -1.0, -1.0, 1.0, 1.0, -1.0, 1.0, -1.0,
    //     -1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, -1.0,
    //     -1.0, 1.0, 1.0, 1.0, 1.0, -1.0, -1.0, 1.0, -1.0,
    //     1.0, -1.0, 1.0, -1.0, -1.0, -1.0, 1.0, -1.0, -1.0,
    //     1.0, -1.0, 1.0, -1.0, -1.0, 1.0, -1.0, -1.0, -1.0
    // };

    float pyramidPositions[54] =
    {
        -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f,
        1.0f, -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f
    };

    float pyrTexCoords[36] =
    {
        0.0f,0.0f,1.0f,0.0f,0.5f,1.0f,    0.0f,0.0f,1.0f,0.0f,0.5f,1.0f,
        0.0f,0.0f,1.0f,0.0f,0.5f,1.0f,    0.0f,0.0f,1.0f,0.0f,0.5f,1.0f,
        0.0f,0.0f,1.0f,1.0f,0.0f,1.0f,    1.0f,1.0f,0.0f,0.0f,1.0f,0.0f
    };

    GLCall(glGenVertexArrays(numVAOs, m_VAO));
    GLCall(glBindVertexArray(m_VAO[0]));
    GLCall(glGenBuffers(numVBOs, m_VBO));

    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_VBO[0]));
    GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(pyramidPositions), pyramidPositions, GL_STATIC_DRAW));

    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_VBO[1]));
    GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(pyrTexCoords), pyrTexCoords, GL_STATIC_DRAW));

}

/**
 * @brief opengl "init" function
 * 
 * This function creates the rendering program from opengl 
 * and generates and binds the vertexArrays
 * 
 */
void Application::init(void) 
{
    m_CameraPos = glm::vec3(0.0f, 0.0f, 5.0f);
    m_PyramPos = glm::vec3(0.0f, 2.0f, 0.0f);
    setUpVertices();

    //build perspective matrix
    glfwGetFramebufferSize(m_Window, &m_Width, &m_Height);
    m_aspect = (float) m_Width / (float) m_Height;
    m_PMat = glm::perspective(1.0472f, m_aspect, 0.1f, 1000.0f);

    std::filesystem::path textpath("textures/brick/Brick_1K_Color.jpg");
    if(std::filesystem::exists(textpath))
    {
        m_Model.loadTextureFromFile(textpath.string().c_str());
    }
};

void Application::window_reshape_callback(GLFWwindow* window, int newWidth, int newHeight)
{
    auto application = reinterpret_cast<Application*>(glfwGetWindowUserPointer(window));
    application->m_aspect = (float) newWidth / (float) newHeight;     // new aspect ratio
    GLCall(glViewport(0, 0, newWidth, newHeight));      // set screen region
    application->m_PMat = glm::perspective(1.0472f, application->m_aspect, 0.1f, 1000.0f);
}

Application::Application()
{
    if(!glfwInit()) {exit(EXIT_FAILURE);}

    //opengl contexts
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    //make window
    m_Window = glfwCreateWindow(600, 600, "Opengl Stuff Window", nullptr, nullptr);
    glfwMakeContextCurrent(m_Window);

    //init glew
    if(glewInit() != GLEW_OK) {exit(EXIT_FAILURE);}



    GLCall(glEnable(GL_DEBUG_OUTPUT));
    GLCall(glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS));
    GLCall(glDebugMessageCallback(debugMessageCallback, nullptr));

    glfwSetWindowUserPointer(m_Window, this);
	glfwSetWindowSizeCallback(m_Window, window_reshape_callback);

    //turn off v-sync
    glfwSwapInterval(1);

    init();

    m_Shader = Shader{"shaders/vertexShaderSimple.glsl", "shaders/fragmentShaderSimple.glsl"};
}

void Application::run()
{
        // handle exit code
    while(!glfwWindowShouldClose(m_Window)) 
    {
        m_CurrentTime = glfwGetTime();
        display();
        glfwSwapBuffers(m_Window);
        glfwPollEvents();
    }

    // termination code
    glfwDestroyWindow(m_Window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}

/**
 * @brief render function
 * 
 * This function repeated draws the info to screen. 
 * 
 * @param window glfw window with opengl context
 * @param currentTime time since window init
 */
void Application::display()
{
    GLCall(glEnable(GL_CULL_FACE));
    GLCall(glClear(GL_DEPTH_BUFFER_BIT));
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
    m_Shader.useProgram();

    // model, view and model-view matrix
    m_VMat = glm::translate(glm::mat4(1.0f), -m_CameraPos);
    // push view matrix
    m_MVStack.push(m_VMat);

    // pyramid stack
    m_MVStack.push(m_MVStack.top());
    m_MVStack.top() *= glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));      // sum position
    m_MVStack.push(m_MVStack.top());
    m_MVStack.top() *= glm::rotate(glm::mat4(1.0f),float(m_CurrentTime), glm::vec3(1.0f,0.0f,0.0f));    // sun rotation

    // copyPerspective and MV matrices to uniforms
    m_Shader.setUniformMat4f("mv_matrix", m_MVStack.top());
    m_Shader.setUniformMat4f("proj_matrix", m_PMat);

    // associate VBO with vertex attribute in m_Shader
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_VBO[0]));
    GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0));
    GLCall(glEnableVertexAttribArray(0));

    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_VBO[1]));
    GLCall(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0));
    GLCall(glEnableVertexAttribArray(1));

    //textures
    GLCall(glActiveTexture(GL_TEXTURE0));
    GLCall(glBindTexture(GL_TEXTURE_2D, m_Model.getTextureID()));



    // adjust opengl settings
    GLCall(glEnable(GL_DEPTH_TEST));
    GLCall(glDepthFunc(GL_LEQUAL));
    GLCall(glFrontFace(GL_CCW));
    GLCall(glDrawArrays(GL_TRIANGLES, 0, 18));      // draw
    m_MVStack.pop();      // remove the sun's rotation from stack
    m_MVStack.pop(); 

}