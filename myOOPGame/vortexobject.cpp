#include "vortexobject.h"
#include <stdlib.h>
#include <ctime>
#include <random>

VortexObject::VortexObject(){}

bool VortexObject::action(Player* player){
     srand(time(0));
     int a = rand() % 4 ;
     Coords c;
     switch(a){
     case 0:
        c = {10,11};
         break;
     case 1:
        c = {5,7};
         break;
     case 2:
        c = {9,3};
         break;
     case 3:
        c = {0,13};
         break;
    }
    player->setCoords(c);
    return true;
}

