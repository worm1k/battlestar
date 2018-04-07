#include "Game.hpp"
#include <stdlib.h>
#include <time.h>
int main()
{
    srand(time(NULL));
    Game* game = Game::getInstance();
    game->run();

    return 0;
}
