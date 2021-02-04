#include "vortexobjectfactory.h"

VortexObject* VortexObjectFactory::makeObject()
{
    VortexObject* obj = new VortexObject();
    return obj;
}
