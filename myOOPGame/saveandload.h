#ifndef SAVEANDLOAD_H
#define SAVEANDLOAD_H
#include <fstream>
#include <string>
#include <controller.h>
#include "saveexception.h"

class SaveAndLoad
{
    Controller& control;
    void strategyLetter(Player& player, char stateLetter);
    void getStateLetter(Player& player, char stateLetter);
public:
    SaveAndLoad(Controller& control);
    void loadGame();
    void saveGame();
};

#endif // SAVEANDLOAD_H
