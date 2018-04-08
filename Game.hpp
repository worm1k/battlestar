#ifndef GAME_HPP
#define GAME_HPP

#include "Player.hpp"
#include "Enemy.hpp"
#include "Missile.hpp"
#include <ncurses.h>

#define UP_ARROW 259
#define DOWN_ARROW 258
#define LEFT_ARROW 260
#define RIGHT_ARROW 261
#define SPACE_KEY 32
const int gMaxWidth = 100;
const int gMaxHeight = 30;
const int gMaxMissiles = 100;
const int gMaxEnemies = 100;
const int gSpawnRate = 10;

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
    void drawMapArray(time_t seconds_elapsed);
    void drawBorders();

    static Game* _instance;
    Game();
    Game(const Game& that);
    Game& operator=(const Game& that);

	GameEntity* _rmap[gMaxHeight][gMaxWidth];
    EntityType _map[gMaxHeight][gMaxWidth];
    Player _player;
	Enemy* _enemies[gMaxEnemies];
	Missile* _missiles[gMaxMissiles];
	int		_score;
	void	resetMoved();
	void	spawnEnemy();
	void	moveEntities();
	void	sleepGame();
	void	move(Player &e, int key);
	void	move(GameEntity *e, int x, int y);
	void	action(int key);
	void	shoot(GameEntity &e, int direction);

};

#endif // GAME_HPP
