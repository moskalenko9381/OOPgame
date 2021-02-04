#include "coinObject.h"

coinObject::coinObject(){}

bool coinObject::action(Player* player){
    player->addCoin();
    return true;
}

WeaponObject::WeaponObject(){}

bool WeaponObject::action(Player* player){
    player->addWeapon();
    return true;
}
