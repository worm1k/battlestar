#ifndef GAME_HPP
#define GAME_HPP

#include "Player.hpp"
#include <ncurses.h>

const int gMaxWidth = 100;
const int gMaxHeight = 30;
const int gMaxMissiles = 5;

enum EntityType {
    PLAYER,
    ENEMY,
    MISSILE,
    SPACE,
};

enum ColorType {
    COLOR_ENEMY = 2,
    COLOR_PLAYER,
    COLOR_MISSILE,
    COLOR_SPACE,
    COLOR_BORDER,
};

class Game
{
public:
    ~Game();
    static Game* getInstance();
    void run();

private:

    void bzeroMap();
    void initColors();
    void drawMapArray();
    void drawBorders();

    static Game* _instance;
    Game();
    Game(const Game& that);
    Game& operator=(const Game& that);

    WINDOW* _win;
    EntityType _map[gMaxHeight][gMaxWidth];
    Player _player;
    // Enemy* _enemies;
    // Missile* _missiles; // player's missiles

};

#endif // GAME_HPP
