#pragma once

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

#include <string>
#include <vector>


class Vertex {

};

class SceneObject {

public:
    SceneObject(std::vector<Vertex> &vertices, std::vector<GLuint> &indices) {
        std::vector<Vertex> m_vertices = vertices;
        std::vector<GLuint> m_indices = indices;
    }

    void Draw() {
        glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

private:
    void InitRender(){
        glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBO);
            glGenBuffers(1, &EBO);

            glBindVertexArray(VAO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);

            glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), &m_vertices[0], GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(GLuint),
                         &m_indices[0], GL_STATIC_DRAW);

        glBindVertexArray(0);
    }

private:
    GLuint VAO, VBO, EBO;
    std::vector<Vertex> m_vertices;
    std::vector<GLuint> m_indices;

    std::string m_name;

    std::vector<SceneObject*> m_children;

};

class Scene {

public:
    Scene(std::string& scene_name) {
        m_scene_name = scene_name;
        m_root =
    }

    void Draw() {
        if (m_root) m_root->Draw();
        for(SceneObject* const child : m_children) {
            child->Draw();
        }
    }

private:
    std::string m_scene_name;

    SceneObject* m_root = nullptr;
    std::vector<SceneObject*> m_children;
};
