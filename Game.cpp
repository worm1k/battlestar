#include "Game.hpp"
#include <stddef.h>

Game* Game::_instance = NULL;

Game::Game()
{
    bzeroMap();
}

Game* Game::getInstance()
{
    if (_instance == NULL) {
        _instance = new Game();
    }

    return _instance;
}

void Game::run()
{

}

void Game::bzeroMap()
{
    for (int i = 0; i < gMaxHeight; ++i) {
        for(int j = 0; j < gMaxWidth; ++j) {
            _map[i][j] = SPACE;
        }
    }
}
