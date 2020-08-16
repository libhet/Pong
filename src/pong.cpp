#include "pong.h"
#include "engine/scene/mesh.h"

Player::Player(const game::Game *game, const std::string &name, game::Vec2f position, size_t width, size_t height, drw::Color color)
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

    m_scene_object->transform.Reset();
    m_scene_object->transform.Translate(m_position.x, m_position.y);
    m_scene_object->transform.Scale(m_width, m_height);
    m_scene_object->SetColor(m_color);
}

Ball::Ball(const game::Game *game, const std::string &name, game::Vec2f position, size_t radius, drw::Color color)
    : game::GameObject(game, name)
{
    m_start_pos = position;
    m_position = m_start_pos;
    m_scene_object = std::make_shared<drw::SceneObject>(m_game->GetShader("default_shader").get(), primitives::square);
    m_radius = radius;
}

void Ball::Update(float dt) {
    m_position = m_start_pos + m_speed * dt;

    m_scene_object->transform.Reset();
    m_scene_object->transform.Translate(m_position.x, m_position.y);
    m_scene_object->transform.Scale(m_radius);
}
