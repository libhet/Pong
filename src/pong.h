#include "game/game.h"
#include "engine/control/control.h"

class Player : public game::GameObject {
public:
    Player(const game::Game *game, const std::string &name) : game::GameObject(game, name) {}
    Player(const game::Game *game, const std::string &name, game::Vec2f position, size_t width, size_t height, drw::Color color);

    void Update(float dt) override;

    void SetSpeed(game::Vec2f speed) {
        m_speed = speed;
    }

private:
    game::Vec2f m_start_pos;
    game::Vec2f m_speed = game::Vec2f(0);
    size_t m_width, m_height;
    drw::Color m_color;
};

class Ball : public game::GameObject {
public:
    Ball(const game::Game *game, const std::string &name) : game::GameObject(game, name) {}
    Ball(const game::Game *game, const std::string &name, game::Vec2f position, size_t radius, drw::Color color);

    void Update(float dt) override;

private:
    game::Vec2f m_start_pos;
    game::Vec2f m_speed = game::Vec2f(0);
    size_t m_radius;
    drw::Color m_color;
};

class PongControl : public drw::Control {
public:
    void KeyCallbackImpl(GLFWwindow* window, int key, int scancode, int action, int mode) override {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
            glfwSetWindowShouldClose(window, GL_TRUE);

        if (key == GLFW_KEY_UP && action == GLFW_PRESS) {
            static_cast<Player*>(m_game->GetGameObject("player2").get())->SetSpeed(game::Vec2f(0,400));
        }

        if (key == GLFW_KEY_UP && action == GLFW_RELEASE) {
            static_cast<Player*>(m_game->GetGameObject("player2").get())->SetSpeed(game::Vec2f(0,0));
        }

        if (key == GLFW_KEY_DOWN && action == GLFW_RELEASE) {
            static_cast<Player*>(m_game->GetGameObject("player2").get())->SetSpeed(game::Vec2f(0,0));
        }

        if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) {
            static_cast<Player*>(m_game->GetGameObject("player2").get())->SetSpeed(game::Vec2f(0,-400));
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
        auto player_1 = AddGameObject(std::make_shared<Player>(this, "player1", game::Vec2f(400,0), 20, 100, drw::color::Flame));
        auto player_2 = AddGameObject(std::make_shared<Player>(this, "player2", game::Vec2f(-400,0), 20, 100, drw::color::Flame));
        auto ball = AddGameObject(std::make_shared<Ball>(this, "ball", game::Vec2f(0,0), 30, drw::color::PinkYarrow));

        auto main_scene = GetScene("main_scene");
        auto root = main_scene->GetRoot();
        root->AddChild(player_1->SceneObject());
        root->AddChild(player_2->SceneObject());
        root->AddChild(ball->SceneObject());
    }
};



