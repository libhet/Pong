#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

class Shader {
public:
    GLuint Program = 0;
    Shader() = default;
    Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
    void Use();
    GLint GetUniformLocation(const GLchar * name);
};






#endif // SHADER_H
