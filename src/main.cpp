#include "headers/Game.h"


int main()
{  
    //for pseudo-random nums
    srand(time(0));

    Game game;
    
    while (game.windowOpen()) {

        game.update();

        game.render();

    }


    return 0;
}