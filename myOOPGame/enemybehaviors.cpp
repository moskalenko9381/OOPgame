#include "enemybehaviors.h"

AttackBehavior::AttackBehavior(){}


void AttackBehavior::action(Player& player){
         player.minusLive(2);
         if (chances >= 2)
             player.minusLive(player.getLives());
}


TheftBehavior::TheftBehavior(){
}

void TheftBehavior::action(Player& player){
    if (player.getCoins()){
         player.addCoin(-1);
         chances++;
    }
     if (chances >= 2)
         player.minusLive(player.getLives());
};


StalkerBehavior::StalkerBehavior(){}


void StalkerBehavior::action(Player& player){
       int a = player.getCoins();
       Coords c;
       switch(a){
       case 0:
          c = {6,6};
          player.minusLive(1);
          break;
       case 1:
          c = {8,8};
          player.minusLive(1);
           break;
       case 2:
          c = {14,1};
          player.addCoin(-1);
           break;
       case 3:
          c = {3,3};
          player.addCoin(-2);
          break;
       case 4:
           player.minusLive(1);
           player.addCoin(-1);
           c = {13,14};
          break;
       case 5:
           chances = 3;
           break;
       default:
           return;
      }
       player.setCoords(c);
};
