#ifndef GAME_HPP
#define GAME_HPP

#include "Player.hpp"

const int gMaxWidth = 100;
const int gMaxHeight = 30;
const int gMaxMissiles = 5;

enum EntityType {
    PLAYER,
    ENEMY,
    MISSILE,
    SPACE,
};

class Game
{
public:
    ~Game();
    static Game* getInstance();
    void run();

private:

    void bzeroMap();

    static Game* _instance;
    Game();
    Game(const Game& that);
    Game& operator=(const Game& that);

    EntityType _map[gMaxHeight][gMaxWidth];
    Player _player;
    Enemy* _enemies;
    Missile* _missiles; // player's missiles

};

#endif // GAME_HPP
