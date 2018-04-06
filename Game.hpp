#ifndef GAME_HPP
#define GAME_HPP

extern const int gMaxWidth;
extern const int gMaxHeight;

enum EntityType {
    PLAYER,
    ENEMY,
    MISSILE,
    SPACE,
};

class Game
{
public:
    ~Game();
    static Game* getInstance();
    void run();

private:

    static Game* _instance;
    Game();
    Game(const Game& that);
    Game& operator=(const Game& that);

    EntityType _map[kIntHeight][kIntWidth];
};

#endif // GAME_HPP
