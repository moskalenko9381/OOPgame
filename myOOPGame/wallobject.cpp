#include "wallobject.h"

WallObject::WallObject(){}

bool WallObject::action(Player* player){
  //  player->minusLive();
    player->addCoin(0);
    return false;
}
