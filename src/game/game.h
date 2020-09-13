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
#include "collider.h"


namespace game {

class Collider;
class CollideBox;
class Game;
//class GameObjectPtr;

class GameObject {
public:
    GameObject(Game *game, const std::string &name)
        :  m_game(game), m_name(name)
    {}

    virtual void Update(float dt) = 0;

    void SetPosition(const Vec2f &pos);

    Vec2f GetPosition() const {
        return m_position;
    }

    void SetAngle(const real &pos);

    void SetGame(Game *game);
    const std::string &Name() {
        return m_name;
    }

    virtual void OnCollisionDetected(
            [[maybe_unused]]const std::shared_ptr<GameObject>& other) {

    }

    std::shared_ptr<CollideBox> GetCollideBox() const;

    drw::SceneObjectPtr SceneObject() const;

protected:
    Game *m_game = nullptr;
    std::string m_name;
    drw::SceneObjectPtr m_scene_object = nullptr;

    Vec2f m_position = Vec2f(0);
    real  m_angle = real(0);
    std::shared_ptr<CollideBox> m_collide_box;
};

using GameObjectPtr = std::shared_ptr<GameObject>;
using GameObjectWeakPtr = std::weak_ptr<GameObject>;


class Game {
public:
    Game(size_t width, size_t height, const std::string& game_name);

    void AddScene(const drw::ScenePtr& scene);
    bool SetScene(const std::string& scene_name);

    template<typename T>
    void SetControl() {
        m_context->SetControl(T::GetInstance(this));
        m_control = &T::GetInstance(this);
    }

    void Start();

    size_t Width() const {return m_width;}
    size_t Height() const {return m_height;}

    drw::ScenePtr GetScene(const std::string &scene_name);

    GameObjectPtr AddGameObject(const GameObjectPtr &game_object);

    drw::ShaderPtr GetShader(const std::string &shader_name) const;

    GameObjectPtr GetGameObject(const std::string &name);

    Collider* GetCollider();

protected:
    virtual void Update();

protected:
    std::shared_ptr<game::Collider> m_collider;  // todo replace pointer
    drw::Control* m_control;
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
