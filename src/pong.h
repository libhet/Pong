#include "game/game.h"
#include "game/collider.h"
#include "game/types.h"
#include "engine/control/control.h"

using namespace game;

class Player : public game::GameObject {
public:
    Player(game::Game *game, const std::string &name) : game::GameObject(game, name) {}
    Player(game::Game *game, const std::string &name, game::Vec2f position, size_t width, size_t height, drw::Color color);

    void Update(float dt) override;

    void SetSpeed(game::Vec2f speed) {
        m_speed = speed;
    }

    const game::Vec2f &GetSpeed() const {
        return m_speed;
    }

    const game::Vec2f & GetPosition() const {
        return m_position;
    }

    void SetPosition(const game::Vec2f & position) {
        m_position = position;
    }

    CollideBoxPtr CollideBox() const {
        return m_collide_box;
    }

private:
    game::Vec2f m_start_pos;
    game::Vec2f m_speed = game::Vec2f(0, 400);
    size_t m_width, m_height;
    drw::Color m_color;
};

using PLayerPtr = std::shared_ptr<Player>;

class Ball : public game::GameObject {
public:
    Ball(game::Game *game, const std::string &name) : game::GameObject(game, name) {}
    Ball(game::Game *game, const std::string &name, game::Vec2f position, size_t radius, drw::Color color);

    void Update(float dt) override;

    CollideBoxPtr CollideBox() const {
        return m_collide_box;
    }

    void OnCollisionDetected(const std::shared_ptr<GameObject>& other) override {
//        std::cout << "Collision!" << std::endl;
        m_speed = game::Vec2f(-1, -1) * m_speed;
    }

private:
    game::Vec2f m_start_pos;
    game::Vec2f m_speed = game::Vec2f(200, 0);
    int m_radius;
    drw::Color m_color;
};

using BallPtr = std::shared_ptr<Ball>;

class PongControl : public drw::Control {
public:
    void KeyCallbackImpl(GLFWwindow* window, int key, int scancode, int action, int mode) override {
        if (key == GLFW_KEY_UNKNOWN) return;

        if(action == GLFW_PRESS) {
            m_pressed[key] = true;
        }
        else if (action == GLFW_RELEASE) {
            m_pressed[key] = false;
        }

        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
            glfwSetWindowShouldClose(window, GL_TRUE);

    }

    static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) {
        GetInstance(nullptr).KeyCallbackImpl(window, key, scancode, action, mode);  // a little hack
    }

    static PongControl & GetInstance(game::Game* game) {
        static PongControl instance(game);
        return instance;
    }

    void HandleInput(float dt) override {

        for(auto key = 0; key < MAX_KEYS; ++key) {
            if(!m_pressed[key]) {
                continue;
            }

            HandleInput_Player1(key, dt, static_cast<Player*>(m_game->GetGameObject("player1").get()));
            HandleInput_Player2(key, dt, static_cast<Player*>(m_game->GetGameObject("player2").get()));
        }

    }

    ~PongControl() = default;

private:
    void HandleInput_Player1(int key, float dt, Player* player) {
        auto position = player->GetPosition();
        auto speed = player->GetSpeed();
        switch (key) {
            case GLFW_KEY_UP:
            position = position + ( speed * dt * UP_DIRECTION);
            player->SetPosition(position);
            break;

            case GLFW_KEY_DOWN:
            position = position + (speed * dt * DOWN_DIRECTION);
            player->SetPosition(position);
            break;
        }
    }

    void HandleInput_Player2(int key, float dt, Player* player) {
        auto position = player->GetPosition();
        auto speed = player->GetSpeed();
        switch (key) {
            case GLFW_KEY_W:
            position = position + (speed * dt * UP_DIRECTION);
            player->SetPosition(position);
            break;

            case GLFW_KEY_S:
            position = position + (speed * dt * DOWN_DIRECTION);
            player->SetPosition(position);
            break;
        }
    }

private:
    PongControl(game::Game* game) : drw::Control(game) { }

    PongControl(const PongControl& other) = delete;
    PongControl(const PongControl&& other) = delete;

    PongControl& operator=(const PongControl& other) = delete;
    PongControl& operator=(const PongControl&& other) = delete;

protected:
    const game::Vec2f UP_DIRECTION = game::Vec2f(0, 1);
    const game::Vec2f DOWN_DIRECTION = game::Vec2f(0, -1);
};

class Pong : public game::Game {
public:
    Pong(size_t width, size_t height, const std::string& game_name);
};



