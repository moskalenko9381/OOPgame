#ifndef WALLOBJECTFACTORY_H
#define WALLOBJECTFACTORY_H
#include "wallobject.h"
#include "objectfactory.h"

class WallObjectFactory: public ObjectFactory
{
public:
     WallObject* makeObject() override;
};


#endif // WALLOBJECTFACTORY_H
