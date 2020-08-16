#include "game.h"

namespace game {

Game::Game(size_t width, size_t height, const std::string& game_name) {
    m_width = width;
    m_height = height;

    m_context = std::make_unique<drw::Context>(width, height, game_name.c_str(), drw::DisplayMode::WINDOWED);

    // You can create shader only after context created
    auto default_shader = std::make_shared<drw::Shader>("shaders/default.vert", "shaders/default.frag");
    m_shaders.insert(std::make_pair("default_shader", default_shader));

//    auto niagara = drw::color::Niagara;
//    auto c = drw::color::PrimroseYellow;
//    auto d = drw::color::Flame;

    auto scene = std::make_shared<drw::Scene>("main_scene", width, height, default_shader.get());
    m_scenes.push_back(scene);
    m_current_scene = scene;

    auto background = scene->GetRoot();
    background->transform.Scale(width, height);
    //    background->transform.Translate(2,0);
    auto l= drw::color::Niagara;
    background->SetColor(l);
    m_context->SetScene(scene);

}

void Game::AddScene(const drw::ScenePtr &scene) {
    m_scenes.push_back(scene);
}

bool Game::SetScene(const std::string &scene_name) {
    auto scene_it = std::find_if(std::begin(m_scenes),
                                 std::end(m_scenes),
                                 [&scene_name](const drw::ScenePtr& s){
        return s->GetSceneName() == scene_name;
    });
    if (scene_it != std::end(m_scenes)) {
        m_current_scene = *scene_it;
        return true;
    }
    return false;
}

void Game::Start() {
    m_context->SetScene(m_current_scene);
    m_context->SetUpdateFunction([this]{Update();});
    m_context->Start();
}

drw::ScenePtr Game::GetScene(const std::string &scene_name) {
    auto scene_it = std::find_if(std::begin(m_scenes),
                                 std::end(m_scenes),
                                 [&scene_name](const drw::ScenePtr& s){
        return s->GetSceneName() == scene_name;
    });
    if (scene_it != std::end(m_scenes)) {
        return *scene_it;
    }
    return nullptr;
}

GameObjectPtr Game::AddGameObject(const GameObjectPtr &game_object) {
    game_object->SetGame(this);
    m_game_objects.push_back(game_object);
    return m_game_objects.back();
}

void Game::Update() {
    auto now = Time::now();
    TimeDelta delta_time = now - m_last_time;
    m_last_time = now;

    // Update all game objects
    for(const auto& game_object : m_game_objects) {
        game_object->Update(delta_time.count());
    }

    // todo: Check scene switching
}

void GameObject::SetPosition(const Vec2f &pos) {
    m_position = pos;
}

void GameObject::SetAngle(const Real &pos) {
    m_angle = pos;
}

void GameObject::SetGame(const Game *game) {
    m_game = game;
}

drw::SceneObjectPtr GameObject::SceneObject() const {
    return m_scene_object;
}

}
