#include <iostream>
#include "engine/style/colors.h"
#include "engine/shader/shader.h"
#include "game/game.h"
//#include "engine/context/context.h"
#include "engine/control/control.h"


GLfloat lineVertices[] = {
    100,100,0,
    200,200,0
};

using namespace drw;

int main()
{
//    auto display = drw::Display(900, 600, "Pong", drw::DisplayMode::WINDOWED);

//    // You can create shader only after context created
//    Shader default_shader = Shader("shaders/default.vert", "shaders/default.frag");

//    auto niagara = drw::color::Niagara;
//    auto c = drw::color::PrimroseYellow;
//    auto d = drw::color::Flame;

//    auto scene = new Scene("main", &default_shader);
//    auto background = scene->GetRoot();
//    background->transform.Scale(900, 600);
////    background->transform.Translate(2,0);
//    background->SetColor(niagara);
//    display.SetScene(scene);
//    display.Start();

    auto game = game::Game(900, 600, "Pong");
    game.SetControl<drw::Control>();
    game.Start();


    return 0;
}




