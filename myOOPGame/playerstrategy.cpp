#include "playerstrategy.h"
#include "player.h"

void WeaponStrategy::algorithm(CellObject* object, Player& player) const{
    player += object;
    if (player.getWeapon() > 4)
         player += object;
};

void VortexStrategy::algorithm(CellObject* object, Player& player) const{
    if (player.vortexes() >= 3)
        return;
    player += object;
    player.addVortex();
};

void CoinStrategy::algorithm(CellObject* object, Player& player) const{
     player += object;
     if (player.getCoins() > 5)
          player += object;
};

void ExitStrategy::algorithm(CellObject* object, Player& player) const{
    player += object;
};

void WallStrategy::algorithm(CellObject* object, Player& player) const{
    player += object;
};

