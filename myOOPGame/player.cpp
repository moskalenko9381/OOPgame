#include "player.h"
#include "field.h"
#include "enemy.h"
#include "enemystate.h"

void Player::changeState(EnemyState* state1){
    DeleteState();
    state = state1;
}

void Player::DeleteState(){
    if (state)
     delete state;
}

EnemyState* Player::getState(){
    return state;
}

Player::Player():coins(0),lives(10), weapon(0),
    takenVortex(0), win(false),coords{0,0}, state(nullptr), strategy(nullptr) {};

void Player::setCoords(Coords c){
    coords.h = c.h;
    coords.w = c.w;
}

void Player::setStart(){
    coins = 0;
    lives = 8;
    win = false;
    coords = {0,0};
}

Coords Player::movePlayer(Dir direction){
    Coords c;
    c.h = coords.h;
    c.w = coords.w;
    switch(direction){
    case UP:
            c.h -=1;
            break;
    case DOWN:
            c.h +=1;
        break;
    case LEFT:
            c.w -=1;
         break;
    case RIGHT:
            c.w +=1;
        break;
      }
   return c;
  }

void Player::stateBegin(){
    if (state)
        delete this->state;

    if (weapon >= 2)
             state = new KillEnemy;

    else if (weapon == 1)
          state = new HurtEnemy;

    else
          state = new HurtPlayer;
}


void Player::addCoin(int size){
    coins += size;
}

void Player::addWeapon(int size){
    weapon += size;
}

bool Player::isWinner(){
    return win;
}

void Player::makeWinner(bool t){
    win = t;
}

void Player::minusLive(int size){
    lives -= size;
}

int Player::getLives(){
    return lives;
}

int Player::getCoins(){
    return coins;
}

int Player::getWeapon(){
    return weapon;
}

int Player::vortexes(){
    return takenVortex;
}

void Player::addVortex(){
    takenVortex++;
}

Coords Player::getCoords(){
    return coords;
}

Player& Player::operator+=(CellObject* object){
    if (!object)
        return (*this);
    object->action(this);
    return *this;
}

Player& Player::operator+=(AbstractEnemy* enemy){
   if (!enemy)
        return (*this);
     enemy->enemyAction(*this);
    return *this;
}

const std::string Player::toString() {
    return  "PLAYER: Coords: " + std::to_string(coords.h) + " ," + std::to_string(coords.w)+ "\n" +
            "        Coins: " +  std::to_string(coins) + "\n" +
            "        Lives: " +  std::to_string(lives) + "\n" +
            "        Win: " + (win ? "true" : "false") + "\n";
}

std::ostream& Player::operator<<(std::ostream &out) {
    return out << toString();
}

void Player::setStrategy(PlayerStrategy *strategy)
{
    if (strategy)
        delete this->strategy;
    this->strategy = strategy;
}


PlayerStrategy* Player::getStrategy(){
    return strategy;
}
