#include "game/game.h"

class Player : public game::GameObject {
public:
    Player(const game::Game *game, const std::string &name) : game::GameObject(game, name) {}
    Player(const game::Game *game, const std::string &name, game::Vec2f position, size_t width, size_t height, drw::Color color);

    void Update(float dt) override;

private:
    game::Vec2f m_start_pos;
    game::Vec2f m_speed;
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
    game::Vec2f m_speed;
    size_t m_radius;
    drw::Color m_color;
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
