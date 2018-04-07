#include "Game.hpp"
#include <unistd.h>
#include <stddef.h>
#include <curses.h>
#include <stdlib.h>

Game* Game::_instance = NULL;

Game::Game()
    : _player(1, 15)
{
    bzeroMap();             // 
    initscr();              // ncurses allocs all it needs
    curs_set(0);            // erase cursor
    cbreak();               // one-character-a-time. Disable the buffering of typed characters
    noecho();               // suppress the automatic echoing from stdin
    nodelay(stdscr, TRUE);  // return ERR if the key input is not ready
    keypad(stdscr, TRUE);   // handle arrow keys with
                            //      KEY_DOWN
                            //      KEY_UP
                            //      KEY_LEFT
                            //      KEY_RIGHT
    // assign colors
}

Game::~Game()
{
    endwin();
    system("clear");
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
    drawFrame()
    while(_player.isAlive())
    {
        // read input with getch()
        // move player,         check horizontal collide
        // create new enemy
        // move missiles,       check collide
        // move enemies,        check collide Ox Oy
        // destroy enemies out of screen
        // destroy missiles out of screen
        // draw _map[][] to screen
        // sleep
    }
}

void Game::bzeroMap()
{
    for (int i = 0; i < gMaxHeight; ++i) {
        for(int j = 0; j < gMaxWidth; ++j) {
            _map[i][j] = SPACE;
        }
    }
}
