#ifndef COINOBJECTFACTORY_H
#define COINOBJECTFACTORY_H
#include "objectfactory.h"
#include "coinObject.h"

class CoinObjectFactory: public ObjectFactory
{
public:
     CellObject* makeObject() override;
};

class WeaponObjectFactory: public ObjectFactory
{
public:
     CellObject* makeObject() override;
};


#endif // COINOBJECTFACTORY_H
