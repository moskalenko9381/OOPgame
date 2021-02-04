#include "wallobjectfactory.h"

WallObject* WallObjectFactory::makeObject() {
    WallObject* obj = new WallObject();
    return obj;
}
