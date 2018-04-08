#include "Game.hpp"
#include <stdlib.h>
#include <ctime>
int main()
{
    srand(time(NULL));
    Game* game = Game::getInstance();
    game->run();
	delete game;

    return 0;
}
