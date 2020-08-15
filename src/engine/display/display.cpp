#include "display.h"

namespace drw {

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

Display::Display(size_t width, size_t height, const char *name, DisplayMode mode)
    : _height(height), _width(width), _name(name)
{
    glfwInit();
    // Set all the required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    if(mode == DisplayMode::FULLSCREEN) {
        _monitor = glfwGetPrimaryMonitor();
    }

    _window = glfwCreateWindow(_width, _height, name, _monitor, nullptr);

    if (_window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }

    // -!- We have to create context before glewInit()
    glfwMakeContextCurrent(_window);

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

Display::~Display() {
    glfwTerminate();
}

void Display::SetScene(Scene *s) {
    _scene = s;
}


void Display::Start()
{

    // Set the required callback functions
    glfwSetKeyCallback(_window, key_callback);

    while (!glfwWindowShouldClose(_window)) // отделить эти штуки
    {
        // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions

        auto now = std::chrono::steady_clock::now();
        std::chrono::duration<float> delta_time = now - m_last_time;
        m_last_time = now;

        if(_scene) {
            _scene->Draw();
            _scene->Update(delta_time.count());
        }

        // Swap the screen buffers
        glfwSwapBuffers(_window);

        glfwPollEvents();
    }
}

void Display::GetFrameBufferSize(int *width, int *height) {
    glfwGetFramebufferSize(_window, width, height);
}



}
