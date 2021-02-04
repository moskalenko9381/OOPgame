#ifndef GAMERULER_H
#define GAMERULER_H
#include "controller.h"
#include "saveandload.h"

class GameRuller
{
    Controller* playerControl;
    Field* field;
public:
    GameRuller(Controller* playerControl,  Field* field);
    ~GameRuller();
    void createGame();
    void endGame();
    void startNewGame();
    void saveGame();
    void loadGame();
};

#endif // GAMERULER_H
