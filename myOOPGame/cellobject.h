#ifndef CELLOBJECT_H
#define CELLOBJECT_H
#include "player.h"

class CellObject {
public:
    virtual bool action(Player *player) = 0;
};

#endif // CELLOBJECT_H
