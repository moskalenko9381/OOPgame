#ifndef ENEMY_H
#define ENEMY_H
#include "enemybehaviors.h"
#include "field.h"

class AbstractEnemy{
  public:
     virtual ~AbstractEnemy() = default;
     virtual void enemyAction(Player& player) = 0;
     virtual void operator+=(Player& player) = 0;
     virtual Coords getCoords() = 0;
     virtual bool isAlive() = 0;
     virtual const std::type_info& getEnemyType() = 0;
     virtual Behavior* getBehavior() = 0;
     virtual int getChances() = 0;
     virtual void setChances(int) = 0;
};



template <class T>
class Enemy: public AbstractEnemy{
    T* behavior;
    Coords coords;
    void enemyAction(Player& player) override;

 public:

    Enemy();
    Enemy(T* behavior, Coords coords):behavior(behavior), coords(coords){};
    void setCoords(Coords c);
    bool isAlive() override;
    void operator+=(Player& player) override;

    void setChances(int lives) override{
        behavior->getChances() = lives;
    }

    Coords getCoords() override;
    Behavior* getBehavior() override;
    const std::type_info& getEnemyType() override{
           return typeid(Enemy<T>);
    }

     int getChances() override{
               return behavior->getChances();
           }
};

template <class T>
bool Enemy<T>::isAlive(){
    return behavior->alive();
}

template <class T>
Behavior* Enemy<T>::getBehavior(){
    return behavior;
}

template <class T>
void Enemy<T>::enemyAction(Player& player){
    behavior->action(player);
}

template <class T>
Coords Enemy<T>::getCoords(){
    return coords;
}

template <class T>
void Enemy<T>::setCoords(Coords c){
    coords.h = c.h;
    coords.w = c.w;
}

template <class T>
void Enemy<T>::operator+=(Player& player){
    this->enemyAction(player);
}


class HurtPlayer: public EnemyState{
  public:
   HurtPlayer();
   void fight(Player* player,AbstractEnemy* enemy) override;
   const std::type_info& getTypeState() override{
          return typeid(HurtPlayer);
   }
};

class KillEnemy: public EnemyState{
  public:
     KillEnemy();
     void fight(Player* player, AbstractEnemy* enemy) override;
     const std::type_info& getTypeState() override{
            return typeid(KillEnemy);
     }
};


class HurtEnemy: public EnemyState{
  public:
    HurtEnemy();
    void fight(Player* player, AbstractEnemy* enemy) override;
    const std::type_info& getTypeState() override{
           return typeid(HurtEnemy);
    }
};


#endif //ENEMY_H

