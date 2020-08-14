#pragma once

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

#include <string>
#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "mesh.h"
#include "../shader/shader.h"
#include "../types/color.h"


class Transformation {
public:
    void SetScale(float x, float y) {
        matrix = glm::scale(matrix, glm::vec3(x, y, 1));
    }
    void SetScale(float x) {
        SetScale(x, x);
    }

    void Translate(float x, float y) {
        matrix = glm::translate(matrix, glm::vec3(x, y, 0.0f));
    }

    void Rotate(float a) {
        matrix = glm::rotate(matrix, a, glm::vec3(0.0f, 0.0f, 1.0f));
    }

    void Reset() {
        matrix = glm::mat4(1.f);
    }

    glm::mat4 matrix = glm::mat4(1.f);
};

class SceneObject {

public:
    SceneObject(Shader* shader, std::vector<Vertex> &vertices, std::vector<GLuint> &indices) {
        std::vector<Vertex> m_vertices = vertices;
        std::vector<GLuint> m_indices = indices;
        m_shader = shader;

        InitRender();
    }

    SceneObject(Shader* shader, Mesh &mesh) {
        m_vertices = mesh.vertices;
        m_indices = mesh.indices;
        m_shader = shader;

        InitRender();
    }

    void SetColor(Color& color) {
        m_color = color;
    }

    void AddChild() {

    }

    void Draw() {
        DrawItself();
        DrawChildren();
    }

    void Update(float dt) {
        UpdateItself(dt);
        UpdateChildren(dt);
    }


public:
    Transformation transform;


private:
    void InitRender(){
        glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBO);
            glGenBuffers(1, &EBO);

            glBindVertexArray(VAO);

            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), &m_vertices[0], GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(GLuint), &m_indices[0], GL_STATIC_DRAW);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
            glEnableVertexAttribArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindVertexArray(0);
    }

    void DrawItself() {
        // shader
        m_shader->Use();

        glBindVertexArray(VAO);

            // color
            glUniform3f(m_shader->GetUniformLocation("ourColor"), m_color.r, m_color.g, m_color.b);

            // transformation
            glUniformMatrix4fv(m_shader->GetUniformLocation("transform"), 1, GL_FALSE, glm::value_ptr(transform.matrix));

            glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

    void DrawChildren() {
        for (SceneObject* child : m_children) {
            child->Draw();
        }
    }

    void UpdateItself(float dt) {

    }

    void UpdateChildren(float dt) {
        for(SceneObject* const child : m_children) {
            child->Update(dt);
        }
    }

private:
    GLuint VAO, VBO, EBO;
    std::vector<Vertex> m_vertices;
    std::vector<GLuint> m_indices;

    Shader* m_shader = nullptr;

    std::string m_name;

    std::vector<SceneObject*> m_children;

    Color m_color = Color(1,1,1,1);

};

class Scene {

public:
    Scene(const char * scene_name, Shader* default_shader) {
        m_scene_name = scene_name;
        m_root = std::make_unique<SceneObject>(default_shader, primitives::square);
    }

    void Draw() {
        if (m_root) m_root->Draw();
    }

    void Update(float dt) {
        if (m_root) m_root->Update(dt);
    }

    SceneObject* get_root() {
        return m_root.get();
    }

private:
    std::string m_scene_name;

    std::unique_ptr<SceneObject> m_root = nullptr;
};
