#include "Game.hpp"
#include <unistd.h>
#include <stddef.h>
#include <stdlib.h>
#include <iostream>
#include <ctime>
#include <sys/time.h>
Game* Game::_instance = NULL;

Game::Game()
    : _player(1, 15)
    , _score(0)
	, _speed(4)
	, _bullets(100)
{
    bzeroMap();             // 
    initscr();              // ncurses allocs all it needs
    curs_set(0);            // erase cursor
    cbreak();               // one-character-a-time. Disable the buffering of typed characters
    noecho();               // suppress the automatic echoing from stdin
    nodelay(stdscr, TRUE);  // return ERR if the key input is not ready
	set_escdelay(25);
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
			if (_rmap[y][x] != NULL && _rmap[y][x]->getType() != "player") {
				delete _rmap[y][x];
				_rmap[y][x] = NULL;
			}
    endwin();
	system("reset");
	std::cout << "Game Over! " << ((_score < 100) ? "You suck. " : "") << "Better luck next time! Your score is " << _score << "!" << std::endl;
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
	init_pair(COLOR_SCENERY, COLOR_WHITE, COLOR_BLACK);
}

void Game::run()
{
	int c;
	int	times = 0;

    drawBorders();
	bzeroMap();
	_rmap[_player.getY()][_player.getX()] = &_player;
	drawMapArray(0);
	const static time_t start_time = std::time(NULL);

	struct timeval te;
	spawnScenery();
    while(_player.isAlive())
    {
		gettimeofday(&te, NULL);
		long long mstart = te.tv_sec * 1000LL + te.tv_usec/1000;

		(++times % 75 == 0) ? ++_bullets : 0;
		c = getch();
		resetMoved();
		if (c != -1)
			action(c);
		spawnEnemy();
		moveEntities();
		drawMapArray(std::time(NULL) - start_time);
        refresh();
		long long mend = te.tv_sec * 1000LL + te.tv_usec/1000;
		usleep(50000 / _speed - (mend - mstart));
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

void Game::spawnScenery() {
	for (int y = 0; y < gMaxHeight; ++y)
		for (int x = 0; x < gMaxWidth; ++x)
			if (_rmap[y][x] == NULL && rand() % 200 == 1)
				_rmap[y][x] = new Scenery(x, y, 0);
}

void Game::spawnEnemy() {
	int ran;
	int	ran2;

	ran2 = rand() % 100;
	if (ran2 < 99 - gSpawnRate)
		return ;
	ran = rand() % gMaxHeight;
	if (_rmap[ran][gMaxWidth - 1] == NULL)
		_rmap[ran][gMaxWidth - 1] = new Enemy(ran, gMaxWidth - 1, -1);
	else if (_rmap[ran][gMaxWidth - 1]->getType() == "player")
		_player.setAlive(false);
}

void Game::bzeroMap()
{
    for (int i = 0; i < gMaxHeight; ++i)
        for(int j = 0; j < gMaxWidth; ++j)
            _rmap[i][j] = NULL;
}

void Game::moveEntities() {
	for (int x = 0; x < gMaxWidth; ++x)
		for (int y = 0; y < gMaxHeight; ++y)
		{
			if (_rmap[y][x] == NULL || _rmap[y][x]->getType() == "player" || _rmap[y][x]->hasMoved())
				continue ;
			else
				move(_rmap[y][x], x, y);
		}
}

void Game::drawMapArray(time_t seconds_elapsed)
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
			else if (_rmap[y][x]->getType() == "scenery")
			{
				attron(COLOR_PAIR(COLOR_SCENERY));
				mvprintw(y + 1, x + 1, "O");
				attroff(COLOR_PAIR(COLOR_SCENERY));
			}

		}
    mvprintw(gMaxHeight + 2, 0, "Score: %d", _score);
	mvprintw(gMaxHeight + 2, gMaxWidth - 90, "Speed: %2d", _speed);
	mvprintw(gMaxHeight + 2, gMaxWidth - 80, "Bullets: %3d", _bullets);
    mvprintw(gMaxHeight + 2, gMaxWidth - 10, "Time: %d", seconds_elapsed);
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
		shoot(_player, 2);
	else if (key == PLUS_KEY)
		incSpeed();
	else if (key == MINUS_KEY)
		decSpeed();
}

void Game::handleCollision(GameEntity **e1, GameEntity **e2) {
	if ((*e1)->getDir() * (*e2)->getDir() < 0 && (*e1)->getTeam() != 2)
	{
		if (((*e1)->getType() == "missile") != ((*e2)->getType() == "missile")) {
			_score += 10;
			_bullets += 3;
		}
			delete *e1;
			*e1 = NULL;
			delete *e2;
			*e2 = NULL;
	}
	else
	{
		delete *e2;
		*e2 = NULL;
	}
}

void Game::shoot(GameEntity &e, int direction) {
	if (e.getX() + 1 < 0 || e.getX() + 1 > gMaxWidth - 1)
		return ;
	if (_rmap[e.getY()][e.getX() + 1] == NULL) {
		if (_bullets > 0) {
			_rmap[e.getY()][e.getX() + 1] = new Missile(e.getX() + 1, e.getY(), direction * (1 + rand() % 2), 0);
			--_bullets;
		}
	}
	else if (_rmap[e.getY()][e.getX() + 1]->getType() != "scenery"){
		delete _rmap[e.getY()][e.getX() + 1];
		_rmap[e.getY()][e.getX() + 1] = NULL;
	}
}

void Game::eshoot(GameEntity &e, int x, int y, int direction) {
	int             ran;

	(void)e;
	ran = rand() % 100;
	if (ran < 95)
		return ;
	if (x + direction < 0 || x + direction > gMaxWidth - 1)
		return ;
	if (_rmap[y][x + direction] == NULL)
		_rmap[y][x + direction] = new Missile(x + direction, y, direction * 2, 1);
	else if (_rmap[y][x + direction]->getType() != "scenery"){
		delete _rmap[y][x + direction];
		_rmap[y][x + direction] = NULL;
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
	if (e->getType() == "enemy")
		eshoot(*e, x, y, (e->getDir() > 0) ? 1 : -1);
	int     ch = (e->getDir() > 0) ? 1 : -1;

	for (int i = ch; (ch > 0) ? i <= e->getDir() : i >= e->getDir(); i += ch)
	{
		if (_rmap[y][x + i - ch] == NULL)
			return ;
		if (x + i < 0 || x + i > gMaxWidth - 1)
		{
			delete _rmap[y][x + i - ch];
			_rmap[y][x + i - ch] = NULL;
			return ;
		}
		else if (_rmap[y][x + i] != NULL)
		{
			if (_rmap[y][x + i]->getType() == "player") {
				_player.setAlive(false);
				return ;
			}
			else if (!_rmap[y][x + i]->hasMoved() && e->getDir() * _rmap[y][x + i]->getDir() > 0)
				move(_rmap[y][x + i], x + i, y);
			else
				return handleCollision(&_rmap[y][x + i], &_rmap[y][x + i - ch]);
		}
		else
		{
			_rmap[y][x + i] = _rmap[y][x + i - ch];
			_rmap[y][x + i - ch] = NULL;
			if (i == e->getDir())
				_rmap[y][x + i]->setMoved(true);
		}
	}
	return ;
}

void Game::incSpeed() {
	if (this->_speed < 10)
		this->_speed++;
}

void Game::decSpeed() {
	if (_speed > 1)
		_speed--;
}
