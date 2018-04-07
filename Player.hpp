#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "GameEntity.hpp"

class Player: public GameEntity
{
public:
    Player();
    Player(const int x, const int y);
    Player(const Player& that);
    ~Player();
    Player& operator=(const Player& that);


private:

    
};

#endif // PLAYER_HPP
