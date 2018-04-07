#include "GameEntity.hpp"

GameEntity::GameEntity()
    : _x(0)
    , _y(0)
    , _isAlive(true)
{}


GameEntity::GameEntity(const int x, const int y)
    : _x(x)
    , _y(y)
    , _isAlive(true)
{}

GameEntity::GameEntity(const GameEntity& that)
    : _x(that.getX())
    , _y(that.getY())
    , _isAlive(that.isAlive())
{}

GameEntity::~GameEntity()
{}

GameEntity& GameEntity::operator=(const GameEntity& that)
{
    if (this != &that)
    {
        _x = that.getX();
        _y = that.getY();
        _isAlive = that.isAlive();
    }
    return *this;
}

const int GameEntity::getX() const
{
    return _x;
}

const int GameEntity::getY() const
{
    return _y;
}

const bool GameEntity::isAlive() const
{
    return _isAlive;
}

void GameEntity::setX(const int x)
{
    _x = x;
}

void GameEntity::setY(const int y)
{
    _y = y;
}

void GameEntity::setAlive(const bool alive)
{
    _isAlive = alive;
}
