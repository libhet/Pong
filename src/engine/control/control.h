#ifndef CONTROL_H
#define CONTROL_H

#include <memory>

#include "../render_open_gl.h"

namespace game {
class Game;
}

namespace drw {

class Control {
public:
    virtual void KeyCallbackImpl(GLFWwindow* window, int key, int scancode, int action, int mode) {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
            glfwSetWindowShouldClose(window, GL_TRUE);
    }

    static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) {
        GetInstance(nullptr).KeyCallbackImpl(window, key, scancode, action, mode);  // a little hack
    }

    static Control & GetInstance(game::Game* game) {
        static Control instance(game);
        return instance;
    }

    virtual void HandleInput(float dt) {}

    virtual ~Control() = default;

    const static int MAX_KEYS = GLFW_KEY_LAST + 1;

protected:
    Control(game::Game* game) : m_game(game) { }

    Control(const Control& other) = delete;
    Control(const Control&& other) = delete;

    Control& operator=(const Control& other) = delete;
    Control& operator=(const Control&& other) = delete;

    game::Game* m_game;
    bool m_pressed[MAX_KEYS] = {false};
};


}

#endif //CONTROL_H
