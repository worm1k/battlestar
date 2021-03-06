#include "Player.hpp"

Player::Player(const int x, const int y)
	: GameEntity(x, y, 0, "player", 0)
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
		setDir(that.getDir());
		setTeam(that.getTeam());
	}
	return (*this);
}
