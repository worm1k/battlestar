#include "GameEntity.hpp"

GameEntity::GameEntity()
    : _x(0)
    , _y(0)
    , _hp(0)
{}


GameEntity::GameEntity(const int x, const int y, const int hp)
    : _x(x)
    , _y(y)
    , _hp(hp)
{}

GameEntity::GameEntity(const GameEntity& that)
    : _x(that.getX())
    , _y(that.getY())
    , _hp(that.getHP())
{}

GameEntity::~GameEntity()
{}

GameEntity& operator=(const GameEntity& that)
{
    if (this != &that)
    {
        _x = that.getX();
        _y = that.getY();
        _hp = that.getHP();
    }
    return *this;
}
