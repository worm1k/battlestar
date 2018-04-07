#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "GameEntity.hpp"

class Player: public GameEntity
{
public:
    Player(const int x, const int y);
    Player(const Player& that);
    virtual ~Player();
    Player& operator=(const Player& that);
private:
	Player();
};

#endif // PLAYER_HPP
