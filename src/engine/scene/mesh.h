#ifndef MESH_H
#define MESH_H

#include <vector>
#include <glm/vec3.hpp>

struct Vertex {
    Vertex(glm::vec3 pos) {
        position = pos;
    }

    glm::vec3 position;
};

struct Mesh {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;  // todo: replace type (unsigned int) -> GLuint
};


namespace primitives {
    static Mesh square = [](){
        Mesh mesh;
        mesh.vertices = {
            Vertex(glm::vec3(0.5f,  0.5f, 0.0f)),
            Vertex(glm::vec3(0.5f, -0.5f, 0.0f)),
            Vertex(glm::vec3(-0.5f, -0.5f, 0.0f)),
            Vertex(glm::vec3(-0.5f,  0.5f, 0.0f))
        };
        mesh.indices = {
            0, 1, 3,
            1, 2, 3
        };
        return mesh;
    }();
}

#endif // MESH_H
