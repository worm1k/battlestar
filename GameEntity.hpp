#ifndef GAMEENTITY_HPP
#define GAMEENTITY_HPP

#include <string>

class GameEntity
{
public:
    GameEntity(const int x, const int y, const int dir, const std::string type, const int team);
    GameEntity(const GameEntity& that);
    virtual ~GameEntity() = 0;
    GameEntity& operator=(const GameEntity& that);

    int getX() const;
    int getY() const;
	int getDir() const;
	std::string getType() const;
    bool isAlive() const;
	bool hasMoved() const;
	int	getTeam() const;

    void setX(const int x);
    void setY(const int y);
	void setDir(const int dir);
	void setType(std::string type);
    void setAlive(const bool alive);
	void setMoved(const bool moved);
	void setTeam(const int team);

private:
    int _x;
    int _y;
	int _dir;
    bool _isAlive;
	bool _hasMoved;
	std::string _type;
	int	_team;
	GameEntity();
};

#endif
