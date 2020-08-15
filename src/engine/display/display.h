#ifndef DISPLAY_H
#define DISPLAY_H

#include "../render_open_gl.h"
#include "../scene/scene.h"

#include <iostream>
#include <functional>
#include <string>
#include <thread>

#include <chrono>

using namespace std::chrono_literals;

namespace drw {


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

enum class DisplayMode {
    WINDOWED = 0,
    FULLSCREEN,

};

class Display {
public:
    Display(size_t width, size_t height, const char *name, DisplayMode mode);
    ~Display();

    void SetScene(Scene* s);
    void Start();

    void GetFrameBufferSize(int* width, int* height);

private:
    GLFWwindow* _window = nullptr;
    GLFWmonitor* _monitor = nullptr;
    size_t _height;
    size_t _width;
    std::string _name;

    Scene* _scene = nullptr;
    std::chrono::steady_clock::time_point m_last_time = std::chrono::steady_clock::now();

};


}

#endif // DISPLAY_H
