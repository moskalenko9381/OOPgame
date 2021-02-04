#ifndef VORTEXOBJECT_H
#define VORTEXOBJECT_H
#include "cellobject.h"

class VortexObject: public CellObject
{
public:
    VortexObject();
    bool action(Player* player);
};

#endif // VORTEXOBJECT_H
