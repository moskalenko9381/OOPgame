#ifndef COINOBJECT_H
#define COINOBJECT_H
#include "cellobject.h"
#include "player.h"

class coinObject: public CellObject
{
public:
    coinObject();
    bool action(Player* player);
};

class WeaponObject: public CellObject
{
public:
    WeaponObject();
    bool action(Player* player);
};


#endif // COINOBJECT_H
