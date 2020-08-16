#include "context.h"

namespace drw {


Context::Context(size_t width, size_t height, const char *name, DisplayMode mode)
    : m_height(height), m_width(width), m_name(name)
{
    glfwInit();
    // Set all the required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    if(mode == DisplayMode::FULLSCREEN) {
        m_monitor = glfwGetPrimaryMonitor();
    }

    m_window = glfwCreateWindow(m_width, m_height, name, m_monitor, nullptr);

    if (m_window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }

    // -!- We have to create context before glewInit()
    glfwMakeContextCurrent(m_window);

    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    const GLenum err = glewInit();
    if (err != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        std::cout << "GLEW Error: " << glewGetErrorString(err) << std::endl;
        glfwTerminate();
    }

    int w, h;
    GetFrameBufferSize(&w, &h);
    glViewport(0, 0, w, h);
}

Context::~Context() {
    glfwTerminate();
}

void Context::SetScene(const ScenePtr& scene) {
    m_scene = scene;
}


void Context::Start()
{

    while (!glfwWindowShouldClose(m_window)) // отделить эти штуки
    {

        if(m_scene) {
            m_scene->Draw();
        }

        if (m_update_fun) m_update_fun();

        // Swap the screen buffers
        glfwSwapBuffers(m_window);

        glfwPollEvents();
    }
}

void Context::GetFrameBufferSize(int *width, int *height) {
    glfwGetFramebufferSize(m_window, width, height);
}





}
