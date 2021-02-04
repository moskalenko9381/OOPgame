#ifndef ENEMYBEHAVIORS_H
#define ENEMYBEHAVIORS_H
#include "player.h"

class Behavior{
  int chances = 0;
public:
  virtual ~Behavior() = default;
  virtual void action(Player& player) = 0;

  void zeroChances(){
      chances = 2;
  }

  void minusLiveEnemy(int size = 1){
            chances += size;
  }

  bool alive(){
     return (chances < 2);
  }

  int& getChances(){
         return chances;
  }

};

class AttackBehavior: public Behavior
{
    int chances = 0;
public:
    AttackBehavior();
    void action(Player& player) override;
};


class TheftBehavior: public Behavior
{
    int chances = 0;

public:
    TheftBehavior();
    void action(Player& player) override;
};


class StalkerBehavior: public Behavior
{
    int chances = 0;

public:
    StalkerBehavior();
    void action(Player& player) override;
};

#endif // ENEMYBEHAVIORS_H */
