#include "GameEntity.hpp"

GameEntity::GameEntity(const int x, const int y, const int dir, const std::string type)
    : _x(x)
    , _y(y)
	, _dir(dir)
    , _isAlive(true)
	, _hasMoved(0)
	, _type(type)
{}

GameEntity::GameEntity(const GameEntity& that)
    : _x(that.getX())
    , _y(that.getY())
	, _dir(that.getDir())
    , _isAlive(that.isAlive())
	, _hasMoved(0)
    , _type(that.getType())
{}

GameEntity& GameEntity::operator=(const GameEntity& that)
{
    if (this != &that)
    {
        _x = that.getX();
        _y = that.getY();
		_dir = that.getDir();
        _isAlive = that.isAlive();
		_hasMoved = that._hasMoved;
    }
    return *this;
}

int GameEntity::getX() const
{
    return _x;
}

int GameEntity::getY() const
{
    return _y;
}

bool GameEntity::isAlive() const
{
    return _isAlive;
}

std::string GameEntity::getType() const {
	return _type;
}

int GameEntity::getDir() const {
	return _dir;
}

bool GameEntity::hasMoved() const {
	return _hasMoved;
}

void GameEntity::setX(const int x)
{
    _x = x;
}

void GameEntity::setY(const int y)
{
    _y = y;
}

void GameEntity::setDir(const int dir) {
	_dir = dir;
}

void GameEntity::setAlive(const bool alive)
{
    _isAlive = alive;
}

void GameEntity::setType(std::string type) {
	_type = type;
}

void GameEntity::setMoved(const bool moved) {
	_hasMoved = moved;
}
