#include "Game.hpp"
#include <unistd.h>
#include <stddef.h>
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
    initColors();
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

void Game::initColors()
{
    start_color();
    init_pair(COLOR_ENEMY, COLOR_YELLOW, COLOR_BLACK);
    init_pair(COLOR_PLAYER, COLOR_RED, COLOR_BLACK);
    init_pair(COLOR_MISSILE, COLOR_CYAN, COLOR_BLACK);
    init_pair(COLOR_SPACE, 16, 16);
    init_pair(COLOR_BORDER, 241, 241);
}

void Game::run()
{
    drawBorders();
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
        refresh();
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

void Game::drawMapArray()
{
}

void Game::drawBorders()
{
    attron(COLOR_PAIR(COLOR_BORDER));
    // top
    for (int x = 0, y = 0; x < gMaxWidth + 2; ++x) {
        mvprintw(y, x, "#");
    }
    // bottom
    for (int x = 0, y = gMaxHeight + 1; x < gMaxWidth + 2; ++x) {
        mvprintw(y, x, "#");
    }
    // left
    for (int x = 0, y = 1; y < gMaxHeight + 1; ++y) {
        mvprintw(y, x, "#");
    }
    // right
    for (int x = gMaxWidth + 1, y = 1; y < gMaxHeight + 1; ++y) {
        mvprintw(y, x, "#");
    }
    attroff(COLOR_PAIR(COLOR_BORDER));
}



























