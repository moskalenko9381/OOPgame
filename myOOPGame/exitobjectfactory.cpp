#include "exitobjectfactory.h"

ExitObject* ExitObjectFactory::makeObject() {
    ExitObject* obj = new ExitObject();
    return obj;
}
