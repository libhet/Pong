#ifndef SHADER_H
#define SHADER_H

#include "../render_open_gl.h"
#include <memory>

namespace drw {


class Shader {
public:
    GLuint Program = 0;
    Shader() = default;
    Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
    void Use();
    GLint GetUniformLocation(const GLchar * name);
};

using ShaderPtr = std::shared_ptr<Shader>;

} // drw

#endif // SHADER_H
