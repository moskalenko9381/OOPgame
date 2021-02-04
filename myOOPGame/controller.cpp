#include "controller.h"
#define COIN 5
#include <fstream>
using namespace std;

Controller::Controller(Player player, Field* field){
    this->player = player;
    this->field = field;
    makeEnemies();
    LoggerHolder::init(new FileLogger("/Users/elizaveta/controller.txt"));
    LoggerHolder::instance().pushLog(new FileLogger("/Users/elizaveta/testlogs.txt"));
    LoggerHolder::instance().pushLog(new ConsoleLogger());
}

void Controller::makeEnemies(){
    enemies.push_back(new Enemy<TheftBehavior>(new TheftBehavior(), {3,3}));
    enemies.push_back(new Enemy<TheftBehavior>(new TheftBehavior(), {12,12}));
    enemies.push_back(new Enemy<AttackBehavior>(new AttackBehavior(), {5,5}));
    enemies.push_back(new Enemy<StalkerBehavior>(new StalkerBehavior(), {10,10}));
}

Controller::~Controller() {
    LoggerHolder::deleteInstance();
    enemies.clear();
}

const std::string Controller::cellInfo(Type type){
    switch(type){
    case CLOSE:
        return "MET A WALL!\n";
    case EXIT:

        if (controlCoinsPlayer() >= 4)
            return "EXIT IS OPENED!";

        return "EXIT IS CLOSED.";
    case VORTEX:
         return "WOW! MET A VORTEX!\n";
    case WEAPON:
        return "YOU PICKED WEAPON!";
     default:
        return "";
    }
}

void Controller::writeMessage(const std::string& change){
     LoggerHolder::instance() << change;
}


bool Controller::checkEnemy(Coords c){
    for (auto enemy: enemies)
           if (enemy->getCoords().h == c.h && enemy->getCoords().w == c.w)
               return true;
       return false;
   }

AbstractEnemy* Controller::getEnemy(Coords c) {
    for (auto enemy : enemies)
        if (enemy->getCoords().h == c.h && enemy->getCoords().w == c.w)
            return enemy;
    return nullptr;
}

Coords Controller::controlMovePlayer(Dir direction){
    if (!(checkCell(player.getCoords(), direction))){
            minusLivePlayer();
            return player.getCoords();
}
    Coords newCoords = player.movePlayer(direction);

  //  player += field->field[newCoords.h][newCoords.w].getObject();   //оператор взаимодействия с объектом

    Type type = field->field[newCoords.h][newCoords.w].getType();

    LoggerHolder::instance() << cellInfo(type);
    CellObject* obj = field->field[newCoords.h][newCoords.w].getObject();

    switch(type){
    case CLOSE:{
            player.setStrategy(new WallStrategy);
            player.getStrategy()->algorithm(obj, player);
            return player.getCoords();
}
    case EXIT:{
         player.setStrategy(new ExitStrategy);
         player.getStrategy()->algorithm(obj, player);
         if (controlCoinsPlayer() < COIN-1)
             return player.getCoords();
}
    case VORTEX:{
           player.setStrategy(new VortexStrategy);
           Coords c = player.getCoords();
           player.getStrategy()->algorithm(obj, player);
           field->field[c.h][c.w].setType(OPEN,nullptr);
           return player.getCoords();
    }
    case COINS:
           player.setStrategy(new CoinStrategy);
           break;
    case WEAPON:
           player.setStrategy(new WeaponStrategy);
           break;
    default:
        break;
    }

    if (obj)
         player.getStrategy()->algorithm(obj, player);

    if(checkEnemy(newCoords)){

        player.stateBegin();
        AbstractEnemy* e = getEnemy(newCoords);
        player.getState()->fight(&player, e);
        LoggerHolder::instance() << "MET AN ENEMY!";

        if (!e->isAlive()){
            enemies.remove(e);
            Coords enemyCoords = e->getCoords();
            std::string info = "ENEMY AT " + std::to_string(enemyCoords.h) + " " + std::to_string(enemyCoords.w) + " IS DEAD\n";
            LoggerHolder::instance() << info;
        }
        return player.getCoords();
}

    if (player.getCoords().h != newCoords.h || player.getCoords().w != newCoords.w){
             Coords old = player.getCoords();
             player.setCoords(newCoords);
             field->field[newCoords.h][newCoords.w].setType(PLAYER,nullptr);
             field->field[old.h][old.w].setType(OPEN,nullptr);
    }
    LoggerHolder::instance() << player.toString();
    return player.getCoords();
}



int Controller::controlLivesPlayer(){
    return player.getLives();
}

int Controller::controlCoinsPlayer(){
    return player.getCoins();
}

Coords Controller::getPlayerCoords(){
    return player.getCoords();
}

bool Controller::playerWin(){
    return player.isWinner();
}

void Controller::minusLivePlayer(int size){
     player.minusLive(size);
}

void Controller::connectObject(CellObject* obj){
    player += obj;
}

int Controller::controlWeaponPlayer(){
    return player.getWeapon();
}

bool Controller::checkCell(Coords coords, Dir direction){
    int y = coords.h;
    int x = coords.w;
    switch(direction){
        case UP:
            return y != 0;
        case DOWN:
            return !(y +1 >= HEIGHT);
        case LEFT:
             return !(x == 0);
        case RIGHT:
            return !(x +1 >= WIDTH);
    }
}

CellObject* Controller::getCellObject(Coords coords){
    return field->field[coords.h][coords.w].getObject();
}

std::list<AbstractEnemy*>& Controller::getEnemies() {
    return enemies;
}

Player& Controller::getPlayer(){
    return player;
}

Field& Controller::getField(){
    return *field;
};
