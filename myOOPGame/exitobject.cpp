#include "exitobject.h"
#define COIN 5
ExitObject::ExitObject(){}

bool ExitObject::action(Player* player){
    if (player->getLives() > 0 && player->getCoins() >= COIN-1){
        player->makeWinner(true);
        return true;
    }
    return false;
}
