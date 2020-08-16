#ifndef CONTEXT_H
#define CONTEXT_H

#include "../control/control.h"
#include "../render_open_gl.h"
#include "../scene/scene.h"

#include <iostream>
#include <functional>
#include <string>
#include <thread>

#include <chrono>

//using namespace std::chrono_literals;

namespace drw {


enum class DisplayMode {
    WINDOWED = 0,
    FULLSCREEN,

};


class Context {
public:
    Context(size_t width, size_t height, const char *name, DisplayMode mode);
    ~Context();

    void SetScene(const ScenePtr& scene);
    void Start();

    void GetFrameBufferSize(int* width, int* height);

    void SetUpdateFunction(std::function<void()> fun) {
        m_update_fun = fun;
    }

    template<typename T>
    void SetControl(T& control) {
        glfwSetKeyCallback(m_window, &std::remove_reference_t<T>::KeyCallback);
    }

private:
    GLFWwindow* m_window = nullptr;
    GLFWmonitor* m_monitor = nullptr;
    size_t m_height;
    size_t m_width;
    std::string m_name;
    std::function<void()> m_update_fun;

    drw::ScenePtr m_scene = nullptr;
    drw::Control* m_control;
};

using ContextPtr = std::unique_ptr<Context>;


}

#endif // CONTEXT_H
