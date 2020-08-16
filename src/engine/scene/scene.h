#ifndef SCENE_H
#define SCENE_H

#include "../render_open_gl.h"

#include <string>
#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "mesh.h"
#include "../shader/shader.h"
#include "../types/color.h"

namespace drw {


class Transformation {
public:
    void Scale(float x, float y);
    void Scale(float x);
    void Translate(float x, float y);
    void Rotate(float a);
    void Reset();

    glm::mat4 matrix = glm::mat4(1.f);
};

class Scene;

class SceneObject {

public:
    SceneObject(Shader *shader, std::vector<Vertex> &vertices, std::vector<GLuint> &indices);
    SceneObject(Shader *shader, Mesh &mesh);

    void SetColor(Color &color);
    void AddChild(const std::shared_ptr<SceneObject> &scene_object);
    void Draw();
    void SetScene(Scene *scene);

private:
    void InitRender();
    void DrawItself();
    void DrawChildren();

public:
    Transformation transform;

private:
    GLuint VAO, VBO, EBO;
    std::vector<Vertex> m_vertices;
    std::vector<GLuint> m_indices;

    Scene * m_scene = nullptr;
    Shader* m_shader = nullptr;

    std::string m_name;

    std::vector<std::shared_ptr<SceneObject>> m_children;

    Color m_color = Color(1,1,1,1);

    glm::mat4 projection_matrix = glm::mat4(1.f);
    glm::mat4 view_matrix = glm::mat4(1.f);

};

using SceneObjectPtr = std::shared_ptr<SceneObject>;
using SceneObjectUPtr = std::unique_ptr<SceneObject>;


class Scene {

public:
    Scene(const char * scene_name, size_t width, size_t height, Shader* default_shader);

    void Draw();

    SceneObject* GetRoot();
    void SetRoot(const SceneObjectPtr &scene_object);
    const std::string &GetSceneName();

    size_t Width() {return m_width;}
    size_t Height() {return m_height;}

private:
    std::string m_scene_name;
    size_t m_width, m_height;
    SceneObjectPtr m_root;
};

using ScenePtr = std::shared_ptr<Scene>;

}


#endif // SCENE_H
