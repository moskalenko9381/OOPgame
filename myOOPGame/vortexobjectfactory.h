#ifndef VORTEXOBJECTFACTORY_H
#define VORTEXOBJECTFACTORY_H
#include "objectfactory.h"
#include "vortexobject.h"

class VortexObjectFactory: public ObjectFactory
{
public:
    VortexObject* makeObject() override;
};

#endif // VORTEXOBJECTFACTORY_H
