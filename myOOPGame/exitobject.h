#ifndef EXITOBJECT_H
#define EXITOBJECT_H
#include "cellobject.h"

class ExitObject: public CellObject
{
public:
    ExitObject();
    bool action(Player* player);
};

#endif // EXITOBJECT_H
