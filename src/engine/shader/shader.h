#ifndef SHADER_H
#define SHADER_H

#include "../render_open_gl.h"


namespace drw {


class Shader {
public:
    GLuint Program = 0;
    Shader() = default;
    Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
    void Use();
    GLint GetUniformLocation(const GLchar * name);
};


} // drw

#endif // SHADER_H
