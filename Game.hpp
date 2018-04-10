#ifndef GAME_HPP
#define GAME_HPP

#include "Player.hpp"
#include "Enemy.hpp"
#include "Missile.hpp"
#include "Scenery.hpp"
#include <ncurses.h>

#define UP_ARROW 259
#define DOWN_ARROW 258
#define LEFT_ARROW 260
#define RIGHT_ARROW 261
#define SPACE_KEY 32
#define PLUS_KEY 61
#define MINUS_KEY 45
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
	SCENERY,
};

enum ColorType {
    COLOR_ENEMY = 2,
    COLOR_PLAYER,
    COLOR_MISSILE,
    COLOR_SPACE,
    COLOR_BORDER,
	COLOR_SCENERY,
};

class Game
{
public:
    ~Game();
    static Game* getInstance();
    void run();
	void incSpeed();
	void decSpeed();

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
	int		_speed;
	int		_bullets;
	void	resetMoved();
	void	spawnEnemy();
	void	spawnScenery();
	void	moveEntities();
	void	sleepGame();
	void	move(Player &e, int key);
	void	move(GameEntity *e, int x, int y);
	void	action(int key);
	void	shoot(GameEntity &e, int direction);
	void	eshoot(GameEntity &e, int x, int y, int direction);
	void	handleCollision(GameEntity **e1, GameEntity **e2);

};

#endif // GAME_HPP
