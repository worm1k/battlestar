#ifndef GAMEENTITY_HPP
#define GAMEENTITY_HPP

class GameEntity
{
public:
    GameEntity();
    GameEntity(const int x, const int y, const int hp);
    GameEntity(const GameEntity& that);
   ~GameEntity();
    GameEntity& operator=(const GameEntity& that);

    const int getX() const;
    const int getY() const;
    const int getHP() const;

    void setX(const int x);
    void setY(const int y);
    void setHP(const int health);

private:
    int _x;
    int _y;
    int _hp;
};

#endif // GAMEENTITY_HPP
