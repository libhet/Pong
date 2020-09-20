#include "pong.h"
#include "engine/scene/mesh.h"

#include "engine/utilities/inpit_utilities.h"

Player::Player(
    game::Game* game,
    const std::string& name,
    game::Vec2f position,
    size_t width,
    size_t height,
    drw::Color color) :
  game::GameObject(game, name)
{
    m_start_pos = position;
    m_position = m_start_pos;
    m_scene_object = std::make_shared<drw::SceneObject>(
        m_game->GetShader("default_shader").get(), primitives::square);
    m_width = width;
    m_height = height;
    m_color = color;
    m_collide_box =
        std::make_shared<game::CollideBox>(m_position, game::Vec2f(20, 100));
}

void Player::Update(float dt)
{
    int half_height = m_game->Height() / 2;
    int limit_height = half_height - m_height / 2;

    if (m_position.y > limit_height)
    {
        m_position.y = limit_height;
    }
    if (m_position.y < -limit_height)
    {
        m_position.y = -limit_height;
    }

    m_scene_object->transform.Reset();
    m_scene_object->transform.Translate(m_position.x, m_position.y);
    m_scene_object->transform.Scale(m_width, m_height);
    m_scene_object->SetColor(m_color);
}

Ball::Ball(
    game::Game* game,
    const std::string& name,
    game::Vec2f position,
    size_t radius,
    drw::Color color) :
  game::GameObject(game, name)
{
    m_start_pos = position;
    m_position = m_start_pos;
    m_scene_object = std::make_shared<drw::SceneObject>(
        m_game->GetShader("default_shader").get(), primitives::square);
    m_radius = radius;
    m_color = color;
    m_collide_box =
        std::make_shared<game::CollideBox>(m_position, game::Vec2f(30, 30));
    //    m_collide_box->SetCollisionFunction([this](const game::CollideBox&
    //    other){CollisionFunction(other);});
}

void Ball::Update(float dt)
{
    m_position = m_position + m_speed * dt;

    m_scene_object->transform.Reset();
    m_scene_object->transform.Translate(m_position.x, m_position.y);
    m_scene_object->transform.Scale(m_radius);
    m_scene_object->SetColor(m_color);
}

Pong::Pong(size_t width, size_t height, const std::string& game_name) :
  game::Game(width, height, game_name)
{
    auto player_1 = AddGameObject(std::make_shared<Player>(
        this, "player1", game::Vec2f(400, 0), 20, 100, drw::color::Flame));
    auto player_2 = AddGameObject(std::make_shared<Player>(
        this, "player2", game::Vec2f(-400, 0), 20, 100, drw::color::Flame));
    auto ball = AddGameObject(std::make_shared<Ball>(
        this, "ball", game::Vec2f(0, 0), 30, drw::color::PinkYarrow));

    auto top = AddGameObject(
        std::make_shared<Border>(this, "top", game::Vec2f(0, 350), 1000, 100));
    auto bottom = AddGameObject(std::make_shared<Border>(
        this, "bottom", game::Vec2f(0, -350), 1000, 100));
    auto left = AddGameObject(
        std::make_shared<Border>(this, "left", game::Vec2f(-500, 0), 100, 1000));
    auto right = AddGameObject(
        std::make_shared<Border>(this, "right", game::Vec2f(500, 0), 100, 1000));

    GetCollider()->AddGameObject(player_1);
    GetCollider()->AddGameObject(player_2);
    GetCollider()->AddGameObject(ball);

    GetCollider()->AddGameObject(top);
    GetCollider()->AddGameObject(bottom);
    GetCollider()->AddGameObject(left);
    GetCollider()->AddGameObject(right);

    auto main_scene = GetScene("main_scene");
    auto root = main_scene->GetRoot();
    root->AddChild(player_1->SceneObject());
    root->AddChild(player_2->SceneObject());
    root->AddChild(ball->SceneObject());
}

void PongControl::KeyCallbackImpl(
    GLFWwindow* window,
    int key,
    [[maybe_unused]] int scancode,
    int action,
    [[maybe_unused]] int mode)
{
    if (key == GLFW_KEY_UNKNOWN)
    {
        key = drw::utilities::ConvertScancodeToKey(scancode, mode);
    }

    if (action == GLFW_PRESS)
    {
        m_pressed[key] = true;
    }
    else if (action == GLFW_RELEASE)
    {
        m_pressed[key] = false;
    }

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}
