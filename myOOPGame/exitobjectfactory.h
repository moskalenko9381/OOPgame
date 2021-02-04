#ifndef EXITOBJECTFACTORY_H
#define EXITOBJECTFACTORY_H
#include "exitobject.h"
#include "objectfactory.h"

class ExitObjectFactory: public ObjectFactory
{
public:
     ExitObject* makeObject() override;
};

#endif // EXITOBJECTFACTORY_H
