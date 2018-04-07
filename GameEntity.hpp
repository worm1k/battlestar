#ifndef GAMEENTITY_HPP
#define GAMEENTITY_HPP

class GameEntity
{
public:
    GameEntity();
    GameEntity(const int x, const int y);
    GameEntity(const GameEntity& that);
    virtual ~GameEntity() = 0;
    GameEntity& operator=(const GameEntity& that);

    const int getX() const;
    const int getY() const;

    void setX(const int x);
    void setY(const int y);

private:
    int _x;
    int _y;
};

#endif // GAMEENTITY_HPP
