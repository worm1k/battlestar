#include "Game.hpp"

const int gMaxWidth = 100;
const int gMaxHeight = 30;
Game* Game::instance = nullptr;

Game::Game()
{
    bzeroMap();
}

static Game* getInstance()
{
    if (_instance == nullptr) {
        instance = new Game();
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
