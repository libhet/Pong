#include "game/game.h"
#include "engine/control/control.h"

class Player : public game::GameObject {
public:
    Player(game::Game *game, const std::string &name) : game::GameObject(game, name) {}
    Player(game::Game *game, const std::string &name, game::vec2 position, size_t width, size_t height, drw::Color color);

    void Update(float dt) override;

    void SetSpeed(game::vec2 speed) {
        m_speed = speed;
    }

private:
    game::vec2 m_start_pos;
    game::vec2 m_speed = game::vec2(0);
    int m_width, m_height;
    drw::Color m_color;
};

class Ball : public game::GameObject {
public:
    Ball(game::Game *game, const std::string &name) : game::GameObject(game, name) {}
    Ball(game::Game *game, const std::string &name, game::vec2 position, size_t radius, drw::Color color);

    void Update(float dt) override;

private:
    game::vec2 m_start_pos;
    game::vec2 m_speed = game::vec2(0);
    int m_radius;
    drw::Color m_color;
};

class PongControl : public drw::Control {
public:
    void KeyCallbackImpl(GLFWwindow* window, int key, int scancode, int action, int mode) override {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
            glfwSetWindowShouldClose(window, GL_TRUE);

        if (key == GLFW_KEY_UP && action == GLFW_PRESS) {
            static_cast<Player*>(m_game->GetGameObject("player2").get())->SetSpeed(game::vec2(0,400));
        }

        if (key == GLFW_KEY_UP && action == GLFW_RELEASE) {
            static_cast<Player*>(m_game->GetGameObject("player2").get())->SetSpeed(game::vec2(0,0));
        }

        if (key == GLFW_KEY_DOWN && action == GLFW_RELEASE) {
            static_cast<Player*>(m_game->GetGameObject("player2").get())->SetSpeed(game::vec2(0,0));
        }

        if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) {
            static_cast<Player*>(m_game->GetGameObject("player2").get())->SetSpeed(game::vec2(0,-400));
        }

        if (key == GLFW_KEY_W && action == GLFW_PRESS) {
            static_cast<Player*>(m_game->GetGameObject("player1").get())->SetSpeed(game::vec2(0,400));
        }

        if (key == GLFW_KEY_W && action == GLFW_RELEASE) {
            static_cast<Player*>(m_game->GetGameObject("player1").get())->SetSpeed(game::vec2(0,0));
        }

        if (key == GLFW_KEY_S && action == GLFW_RELEASE) {
            static_cast<Player*>(m_game->GetGameObject("player1").get())->SetSpeed(game::vec2(0,0));
        }

        if (key == GLFW_KEY_S && action == GLFW_PRESS) {
            static_cast<Player*>(m_game->GetGameObject("player1").get())->SetSpeed(game::vec2(0,-400));
        }
    }

    static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) {
        GetInstance(nullptr).KeyCallbackImpl(window, key, scancode, action, mode);  // a little hack
    }

    static PongControl & GetInstance(game::Game* game) {
        static PongControl instance(game);
        return instance;
    }

    virtual ~PongControl() = default;

private:
    PongControl(game::Game* game) : drw::Control(game) { }

    PongControl(const PongControl& other) = delete;
    PongControl(const PongControl&& other) = delete;

    PongControl& operator=(const PongControl& other) = delete;
    PongControl& operator=(const PongControl&& other) = delete;
};

class Pong : public game::Game {
public:
    Pong(size_t width, size_t height, const std::string& game_name)
        : game::Game(width, height, game_name)
    {
        auto player_1 = AddGameObject(std::make_shared<Player>(this, "player1", game::vec2(400,0), 20, 100, drw::color::Flame));
        auto player_2 = AddGameObject(std::make_shared<Player>(this, "player2", game::vec2(-400,0), 20, 100, drw::color::Flame));
        auto ball = AddGameObject(std::make_shared<Ball>(this, "ball", game::vec2(0,0), 30, drw::color::PinkYarrow));

        auto main_scene = GetScene("main_scene");
        auto root = main_scene->GetRoot();
        root->AddChild(player_1->SceneObject());
        root->AddChild(player_2->SceneObject());
        root->AddChild(ball->SceneObject());
    }
};



