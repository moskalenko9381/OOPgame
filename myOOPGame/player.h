#ifndef PLAYER_H
#define PLAYER_H
#include "direction.h"
#include "coords.h"
#include <string>
#include "playerstrategy.h"

class CellObject;
class AbstractEnemy;
class Behavior;
class Player;

class EnemyState
{
public:
    virtual ~EnemyState() = default;
    virtual void fight(Player* player, AbstractEnemy* enemy) = 0;
    virtual const std::type_info& getTypeState() = 0;
};

class Player
{
    int coins;
    int lives;
    int weapon;
    int takenVortex;
    bool win;
    Coords coords;
    EnemyState* state;
    PlayerStrategy* strategy;
public:
    friend class EnemyState;
    friend class SaveAndLoad;
    void DeleteState();
    EnemyState* getState();
    PlayerStrategy* getStrategy();
    Player();
    void setStart();
    void setStrategy(PlayerStrategy *strategy);

    Player& operator+=(CellObject* object);
    Player& operator+=(AbstractEnemy* enemy);

    void changeState(EnemyState* state1);
    void stateBegin();
    bool isWinner();

    void setCoords(Coords c);

    void addCoin(int size = 1);
    void addWeapon(int size = 1);
    void makeWinner(bool t);
    void minusLive(int size = 1);
    void addVortex();

    int getLives();
    int getCoins();
    int getWeapon();
    int vortexes();

    Coords movePlayer(Dir direction);
    Coords getCoords();

    const std::string toString();
    std::ostream& operator<<(std::ostream &output);
};

#endif
