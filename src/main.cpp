#include <iostream>
#include "engine/window/main_window.h"
#include "engine/style/colors.h"
#include "engine/shader/shader.h"


GLfloat lineVertices[] = {
    100,100,0,
    200,200,0
};



int main()
{
    auto _window = drw::MainWindow(900, 600, "Pong", drw::WindowMode::WINDOWED);

    // You can create shader only after context created
    Shader default_shader = Shader("C:/cpp_projects/something-to-draw/src/shaders/default.vert",
                                   "C:/cpp_projects/something-to-draw/src/shaders/default.frag");

    GLint color_location = default_shader.GetUniformLocation("ourColor");

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho(0, 640, 0, 640, 0, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // ---
    GLfloat vertices[] = {
         0.5f,  0.5f, 0.0f,  // Top Right
         0.5f, -0.5f, 0.0f,  // Bottom Right
        -0.5f, -0.5f, 0.0f,  // Bottom Left
        -0.5f,  0.5f, 0.0f   // Top Left
    };
    GLuint indices[] = {  // Note that we start from 0!
        0, 1, 3,  // First Triangle
        1, 2, 3   // Second Triangle
    };
    GLuint VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

    glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs), remember: do NOT unbind the EBO, keep it bound to this VAO
    // ---


    // Game loop
    auto niagara = drw::color::Niagara;
    auto c = drw::color::PrimroseYellow;
    auto d = drw::color::Flame;
    _window.SetRenderFunction([&niagara, &c, &default_shader, &color_location, &VAO, &d](){


        glClearColor(niagara.r, niagara.g, niagara.b, niagara.a);
        glClear(GL_COLOR_BUFFER_BIT);

        default_shader.Use();
        glUniform3f(color_location, c.r, c.g, c.b);
        glBindVertexArray(VAO);
        //glDrawArrays(GL_TRIANGLES, 0, 6);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glUniform3f(color_location, d.r, d.g, d.b);
                    glLineWidth(5);
                    glEnable(GL_LINE_SMOOTH);
        glDrawElements(GL_LINE_STRIP, 3, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

//        glEnableClientState(GL_VERTEX_ARRAY);
//            default_shader.Use();
//            glUniform3f(color_location, c.r, c.g, c.b);
//            glColor3f(c.r, c.g, c.b);
//            glEnable(GL_LINE_SMOOTH);
//            glLineWidth(100);
//            glVertexPointer(3, GL_FLOAT, 0, lineVertices);
//            glDrawArrays(GL_LINES, 0, 2);
//            glDisable(GL_LINE_SMOOTH);
//        glDisableClientState(GL_VERTEX_ARRAY);


    });

    _window.Start();

    glfwTerminate();
    return 0;
}



/*

  Сделать класс GraphicsNode - дерево таких же нодов. рисует себя и своих детей
  c методомами
  draw(Render *render, Shader *shader)

  Draw()

  std::vector<GraphicsNode> m_childs;
  
  

 */



