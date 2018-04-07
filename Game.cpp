#include "Game.hpp"
#include <unistd.h>
#include <stddef.h>
#include <stdlib.h>
#include <iostream>
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
	for (int y = 0; y < gMaxHeight; y++)
		for (int x = 0; x < gMaxWidth; x++)
			if (_rmap[y][x] != NULL) {
				delete _rmap[y][x];
				_rmap[y][x] = NULL;
			}
    endwin();
	system("clear");
	std::cout << "Game Over! You suck. Better luck next time!" << std::endl;
}

Game* Game::getInstance()
{
    if (_instance == NULL)
        _instance = new Game();

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
	int c;

    drawBorders();
	bzeroMap();
	_rmap[_player.getY()][_player.getX()] = &_player;
	drawMapArray();
    while(_player.isAlive())
    {
		resetMoved();
		// read input with getch()
		c = getch();
		// move player
		if (c != -1)
			action(c);
        // create new enemy
		spawnEnemy();
		// move entities
		// destroy enemies out of screen
		// destroy missiles out of screen
		moveEntities();
        // draw _map[][] to screen
		drawMapArray();
        // sleep
        refresh();
		rmDelay();
    }
}

void Game::resetMoved()
{
	for (int y = 0; y < gMaxHeight; y++)
		for (int x = 0; x < gMaxWidth; x++) {
			if (_rmap[y][x] != NULL) {
				if (_rmap[y][x]->getType() == "player")
					_rmap[y][x]->setMoved(true);
				else
					_rmap[y][x]->setMoved(false);
			}
		}
}

void Game::spawnEnemy() {
	int ran;
	int	ran2;

	ran2 = rand() % 100;
	if (ran2 < 99 - gSpawnRate)
		return ;
	ran = rand() % gMaxHeight;
	if (_rmap[ran][gMaxWidth - 1] == NULL)
		_rmap[ran][gMaxWidth - 1] = new Enemy(ran, gMaxWidth, -1);
	else if (_rmap[ran][gMaxWidth - 1]->getType() == "player")
		_player.setAlive(false);
}

void Game::rmDelay() {
	nodelay(stdscr, TRUE);
	double pause = 1.0 / 30;
	usleep(pause * 1000000.0);
}

void Game::bzeroMap()
{
    for (int i = 0; i < gMaxHeight; ++i)
        for(int j = 0; j < gMaxWidth; ++j)
            _rmap[i][j] = NULL;
}

void Game::moveEntities() {
	for (int y = 0; y < gMaxHeight; y++)
		for (int x = 0; x < gMaxWidth; x++)
		{
			if (_rmap[y][x] == NULL || _rmap[y][x]->getType() == "player" || _rmap[y][x]->hasMoved())
				continue ;
			else
				move(_rmap[y][x], x, y);
		}
}

void Game::drawMapArray()
{
	for (int x = 0; x < gMaxWidth; x++)
		for (int y = 0; y < gMaxHeight; y++)
		{
			if (_rmap[y][x] == NULL)
			{
				attron(COLOR_PAIR(COLOR_SPACE));
				mvprintw(y + 1, x + 1, " ");
				attroff(COLOR_PAIR(COLOR_SPACE));
			} else if (_rmap[y][x]->getType() == "player") {
				attron(COLOR_PAIR(COLOR_PLAYER));
				mvprintw(y + 1, x + 1, ">");
				attroff(COLOR_PAIR(COLOR_PLAYER));
			} else if (_rmap[y][x]->getType() == "enemy") {
				attron(COLOR_PAIR(COLOR_ENEMY));
				mvprintw(y + 1, x + 1, "X");
				attroff(COLOR_PAIR(COLOR_ENEMY));
			} else if (_rmap[y][x]->getType() == "missile") {
				attron(COLOR_PAIR(COLOR_MISSILE));
				mvprintw(y + 1, x + 1, "-");
				attroff(COLOR_PAIR(COLOR_MISSILE));
			}

		}
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

void Game::action(int key) {
	if (key >= DOWN_ARROW && key <= RIGHT_ARROW)
		move(_player, key);
	else if (key == SPACE_KEY)
		shoot(_player, 1);
}

void Game::shoot(GameEntity &e, int direction) {
	if (e.getX() + direction < 0 || e.getX() + direction > gMaxWidth - 1)
		return ;
	if (_rmap[e.getY()][e.getX() + direction] == NULL) {
		_rmap[e.getY()][e.getX() + direction] = new Missile(e.getX() + direction, e.getY(), direction);
	}
	else {
		delete _rmap[e.getY()][e.getX() + direction];
		_rmap[e.getY()][e.getX() + direction] = NULL;
	}
}

void Game::move(Player &e, int key) {
	int	xch = 0;
	int ych = 0;

	if (key == UP_ARROW && e.getY() > 0)
		ych = -1;
	else if (key == DOWN_ARROW && e.getY() < gMaxHeight - 1)
		ych = 1;
	else if (key == LEFT_ARROW && e.getX() > 0)
		xch = -1;
	else if (key == RIGHT_ARROW && e.getX() < gMaxWidth - 1)
		xch = 1;
	if (e.getY() + ych < 0 || e.getY() + ych > gMaxHeight - 1 || e.getX() + xch < 0 || e.getX() + xch > gMaxWidth - 1 || (xch == 0 && ych == 0))
		return ;
	if (_rmap[e.getY() + ych][e.getX() + xch] != NULL)
		_player.setAlive(false);
	else {
		_rmap[e.getY()][e.getX()] = NULL;
		e.setX(e.getX() + xch);
		e.setY(e.getY() + ych);
		_rmap[e.getY()][e.getX()] = &e;
	}
	return;
}

void Game::move(GameEntity *e, int x, int y) {
	if (x + e->getDir() < 0 || x + e->getDir() > gMaxWidth - 1)
	{
		delete _rmap[y][x];
		_rmap[y][x] = NULL;
	}
	else if (_rmap[y][x + e->getDir()] != NULL)
	{
		if (_rmap[y][x + e->getDir()]->getType() == "player")
			_player.setAlive(false);
		else if (!_rmap[y][x + e->getDir()]->hasMoved() && _rmap[y][x]->getDir() + _rmap[y][x + e->getDir()]->getDir() != 0)
			move(_rmap[y][x + e->getDir()], x + e->getDir() + _rmap[y][x + e->getDir()]->getDir(), y);
		else {
			delete _rmap[y][x + e->getDir()];
			_rmap[y][x + e->getDir()] = NULL;
			delete _rmap[y][x];
			_rmap[y][x] = NULL;
		}
	}
	else
	{
		_rmap[y][x + e->getDir()] = _rmap[y][x];
		_rmap[y][x + e->getDir()]->setMoved(true);
		_rmap[y][x] = NULL;
	}
	return ;
}



























