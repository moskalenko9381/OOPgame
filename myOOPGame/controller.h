#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "field.h"
#include "player.h"
#include "loggerholder.h"
#include "enemy.h"

class Controller
{
    Player player;
    Field* field;
public:
    std::list<AbstractEnemy*> enemies;
    std::list<AbstractEnemy*> &getEnemies();
    AbstractEnemy* getEnemy(Coords c);

    friend class GameRuller;
    Controller(Player player, Field* field);
    ~Controller();
    Coords controlMovePlayer(Dir direction);
    Coords getPlayerCoords();
    int controlLivesPlayer();
    int controlCoinsPlayer();
    int controlWeaponPlayer();
    bool playerWin();
    void writeMessage(const std::string& change);
    void minusLivePlayer(int size = 1);
    void makeEnemies();
    void connectObject(CellObject* obj);
    bool checkCell(Coords coords, Dir direction);
    bool checkEnemy(Coords c);
    CellObject* getCellObject(Coords coords);
    const std::string cellInfo(Type type);


    Player& getPlayer();
    Field& getField();

};

#endif // CONTROLLER_H
