#ifndef GAME_H
#define GAME_H

#include "../engine/context/context.h"
#include "../engine/scene/scene.h"
#include "../engine/control/control.h"
#include "../engine/shader/shader.h"
#include "../engine/style/colors.h"
#include "types.h"
#include <vector>
#include <string>
#include <algorithm>
#include <memory>
#include <unordered_map>

namespace drw {
class Context;
using ContextPtr = std::unique_ptr<Context>;
}

namespace game {

class Game;

class GameObject {
public:
    virtual void Update(float dt) = 0;

    void SetPosition(const Vec2f& pos);

    void SetAngle(const Real& pos);

private:
    drw::SceneObjectPtr m_scene_object = nullptr;

    Vec2f m_position = Vec2f(0);
    Real  m_angle = Real(0);
};

using GameObjectPtr = std::shared_ptr<GameObject>;


class Game {
public:
    Game(size_t width, size_t height, const std::string& game_name);

    void AddScene(const drw::ScenePtr& scene);
    bool SetScene(const std::string& scene_name);

    template<typename T>
    void SetControl() {
        m_context->SetControl(T::GetInstance(this));
    }

    void Start();

private:
    void Update();

private:
    std::vector<drw::ScenePtr> m_scenes;
    std::vector<GameObjectPtr> m_game_objects;
    std::unordered_map<std::string, drw::ShaderPtr> m_shaders;
    drw::ScenePtr m_current_scene = nullptr;
    drw::ContextPtr m_context;
    size_t m_width, m_height;
    TimePoint m_last_time = Time::now();
};

}


#endif // GAME_H
