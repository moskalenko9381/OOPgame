#include "coinobjectfactory.h"

CellObject* CoinObjectFactory::makeObject() {
    coinObject* obj = new coinObject();
    return obj;
}

CellObject* WeaponObjectFactory::makeObject() {
    WeaponObject* obj = new WeaponObject();
    return obj;
}
