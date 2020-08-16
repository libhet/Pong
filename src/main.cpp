#include "pong.h"

using namespace drw;

int main()
{
    auto game = Pong(900, 600, "Pong");
    game.SetControl<PongControl>();
    game.Start();

    return 0;
}




