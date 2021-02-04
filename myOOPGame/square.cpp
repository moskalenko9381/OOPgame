#include "square.h"


Type Square::getType(){
    return type;
}

void Square::setType(Type type, CellObject* obj){
    this->type = type;
    object = obj;
}



void Square::setDestroyed(){
    type = CLOSE;
}

Coords Square::getCoords(){
    return coords;
}

void Square::setH(int h){
    coords.h = h;
}
void Square::setW(int w){
    coords.w = w;
}

CellObject* Square::getObject(){
    return object;
}

void Square::setObject(Type t){
    switch(t){
        case CLOSE:
             setType(CLOSE, new WallObject);
             return;

   case EXIT:
        setType(EXIT, new ExitObject);
        return;
   case COINS:
        setType(COINS, new coinObject);
        return;
   case PLAYER:
        setType(PLAYER);
        return;
   case VORTEX:
        setType(VORTEX, new VortexObject);
        return;
   case WEAPON:
        setType(WEAPON, new WeaponObject);
        return;
    default:
        setType(OPEN);
    }
}
