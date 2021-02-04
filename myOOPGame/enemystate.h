#ifndef ENEMYSTATE_H
#define ENEMYSTATE_H
#include "player.h"
#include "enemy.h"

HurtPlayer::HurtPlayer(){};

KillEnemy::KillEnemy(){};

HurtEnemy::HurtEnemy(){};


void HurtPlayer::fight(Player* player,AbstractEnemy* enemy){
    *enemy += *player;

     if (player->getWeapon() == 1){
          player->changeState(new HurtEnemy());
        }
    else if (player->getWeapon() >= 2)
      player->changeState(new KillEnemy());
 }


void KillEnemy::fight(Player* player, AbstractEnemy* enemy){
    enemy->getBehavior()->zeroChances();
    player->addWeapon(-2);
    if (player->getWeapon() == 1)
         player->changeState(new HurtEnemy());
   else if (player->getWeapon() < 1)
      player->changeState(new HurtPlayer());
 }

void HurtEnemy::fight(Player* player, AbstractEnemy* enemy){
    enemy->getBehavior()->minusLiveEnemy();
    player->addWeapon(-1);
    player->changeState(new HurtPlayer());
};

#endif // ENEMYSTATE_H
