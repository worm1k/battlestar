#include "GameEntity.hpp"

GameEntity::GameEntity()
    : _x(0)
    , _y(0)
{}


GameEntity::GameEntity(const int x, const int y)
    : _x(x)
    , _y(y)
{}

GameEntity::GameEntity(const GameEntity& that)
    : _x(that.getX())
    , _y(that.getY())
{}

GameEntity::~GameEntity()
{}

GameEntity& GameEntity::operator=(const GameEntity& that)
{
    if (this != &that)
    {
        _x = that.getX();
        _y = that.getY();
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

void GameEntity::setX(const int x)
{
    _x = x;
}

void GameEntity::setY(const int y)
{
    _y = y;
}
