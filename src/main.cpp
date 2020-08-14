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
    auto display = drw::Display(900, 600, "Pong", drw::DisplayMode::WINDOWED);

    // You can create shader only after context created
    Shader default_shader = Shader("shaders/default.vert", "shaders/default.frag");

    auto niagara = drw::color::Niagara;
    auto c = drw::color::PrimroseYellow;
    auto d = drw::color::Flame;

    auto scene = new Scene("main", &default_shader);
//    scene->get_root()->transform.Translate(1,1);
    display.SetScene(scene);
    display.Start();


    return 0;
}




