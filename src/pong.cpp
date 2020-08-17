#include "pong.h"
#include "engine/scene/mesh.h"

Player::Player(game::Game *game, const std::string &name, game::vec2 position, size_t width, size_t height, drw::Color color)
    : game::GameObject(game, name)
{
    m_start_pos = position;
    m_position = m_start_pos;
    m_scene_object = std::make_shared<drw::SceneObject>(m_game->GetShader("default_shader").get(), primitives::square);
    m_width = width;
    m_height = height;
    m_color = color;

}

void Player::Update(float dt) {
    m_position += m_speed * dt;

    int half_height = m_game->Height()/2;
    int limit_height = half_height - m_height/2;

    if (m_position.y > limit_height) { m_position.y = limit_height; }
    if (m_position.y < -limit_height) { m_position.y = -limit_height;}

    m_scene_object->transform.Reset();
    m_scene_object->transform.Translate(m_position.x, m_position.y);
    m_scene_object->transform.Scale(m_width, m_height);
    m_scene_object->SetColor(m_color);
}

Ball::Ball(game::Game *game, const std::string &name, game::vec2 position, size_t radius, drw::Color color)
    : game::GameObject(game, name)
{
    m_start_pos = position;
    m_position = m_start_pos;
    m_scene_object = std::make_shared<drw::SceneObject>(m_game->GetShader("default_shader").get(), primitives::square);
    m_radius = radius;
    m_color = color;
}

void Ball::Update(float dt) {
    m_position = m_start_pos + m_speed * dt;


    m_scene_object->transform.Reset();
    m_scene_object->transform.Translate(m_position.x, m_position.y);
    m_scene_object->transform.Scale(m_radius);
    m_scene_object->SetColor(m_color);
}
