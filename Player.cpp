#include "Player.hpp"

Player::Player()
	: GameEntity()
{}

Player::Player(const int x, const int y)
	: GameEntity(x, y)
{}

Player::Player(const Player& that)
	: GameEntity(that)
{}

Player::~Player()
{}

Player& Player::operator=(const Player& that)
{
	if (this != &that) {
		setX(that.getX());
		setY(that.getY());
		setAlive(that.isAlive());
	}
	return (*this);
}
