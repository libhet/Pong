#pragma once

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

#include <iostream>
#include <functional>
#include <string>
#include <thread>

namespace drw {

namespace  {

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

enum class WindowMode {
    WINDOWED = 0,
    FULLSCREEN,

};

class MainWindow {
private:
    GLFWwindow* _window = nullptr;
    GLFWmonitor* _monitor = nullptr;
    size_t _height;
    size_t _width;
    std::string _name;
    std::function<void(void)> _render_function; // сделать ее указателем на метод класса RenderBase::Render

public:
    MainWindow(size_t width, size_t height, const char *name, WindowMode mode)
        : _height(height), _width(width), _name(name)
    {
        glfwInit();
        // Set all the required options for GLFW
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

         if(mode == WindowMode::FULLSCREEN) {
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

    void SetRenderFunction(std::function<void(void)> function)
    {
        _render_function = function;
    }

    void Start()
    {

        // Set the required callback functions
        glfwSetKeyCallback(_window, key_callback);

        while (!glfwWindowShouldClose(_window))
        {
            // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions


            // Render
            _render_function();

            // Swap the screen buffers
            glfwSwapBuffers(_window);

            glfwPollEvents();
        }
    }

    void Stop()
    {

    }

    void GetFrameBufferSize(int* width, int* height) {
        glfwGetFramebufferSize(_window, width, height);
    }

};


}
}
