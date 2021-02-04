#ifndef OBJECTFACTORY_H
#define OBJECTFACTORY_H
#include "cellobject.h"

class ObjectFactory{
    public:
       virtual ~ObjectFactory(){}
       virtual CellObject* makeObject() = 0;
};

#endif // OBJECTFACTORY_H
