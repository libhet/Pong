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
    GameObject(Game *game, const std::string &name)
        :  m_game(game), m_name(name)
    {}

    virtual void Update(float dt) = 0;

    void SetPosition(const vec2 &pos);

    void SetAngle(const real &pos);

    void SetGame(Game *game);
    const std::string &Name() {
        return m_name;
    }

    drw::SceneObjectPtr SceneObject() const;

protected:
    Game *m_game = nullptr;
    std::string m_name;
    drw::SceneObjectPtr m_scene_object = nullptr;

    vec2 m_position = vec2(0);
    real  m_angle = real(0);
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

    size_t Width() const {return m_width;}
    size_t Height() const {return m_height;}

    drw::ScenePtr GetScene(const std::string &scene_name);

    GameObjectPtr AddGameObject(const GameObjectPtr &game_object);

    drw::ShaderPtr GetShader(const std::string &shader_name) const;

    GameObjectPtr GetGameObject(const std::string &name);

protected:
    virtual void Update();

protected:
    std::vector<drw::ScenePtr> m_scenes;
    std::vector<GameObjectPtr> m_game_objects;
    std::unordered_map<std::string, drw::ShaderPtr> m_shaders;
    drw::ScenePtr m_current_scene = nullptr;
    drw::ContextPtr m_context;
    int m_width, m_height;
    TimePoint m_last_time = Time::now();
};

}


#endif // GAME_H
