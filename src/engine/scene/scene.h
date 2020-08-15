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

class Projection {
    Projection() {

    }

    glm::mat4 matrix = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f );
};

class SceneObject {

public:
    SceneObject(Shader* shader, std::vector<Vertex> &vertices, std::vector<GLuint> &indices);
    SceneObject(Shader* shader, Mesh &mesh);

    void SetColor(Color& color);
    void AddChild();
    void Draw();
    void Update(float dt);

private:
    void InitRender();
    void DrawItself();
    void DrawChildren();
    void UpdateItself(float dt);
    void UpdateChildren(float dt);


public:
    Transformation transform;

private:
    GLuint VAO, VBO, EBO;
    std::vector<Vertex> m_vertices;
    std::vector<GLuint> m_indices;

    Shader* m_shader = nullptr;

    std::string m_name;

    std::vector<SceneObject*> m_children;

    Color m_color = Color(1,1,1,1);

    glm::mat4 projection_matrix = glm::mat4(1.f);
    glm::mat4 view_matrix = glm::mat4(1.f);

};

class Scene {

public:
    Scene(const char * scene_name, Shader* default_shader);

    void Draw();
    void Update(float dt);

    SceneObject* GetRoot();

private:
    std::string m_scene_name;
    std::unique_ptr<SceneObject> m_root = nullptr;
};

}


#endif // SCENE_H
