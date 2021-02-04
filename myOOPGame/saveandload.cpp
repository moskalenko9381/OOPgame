#include "saveandload.h"
#include "field.h"
#include <iostream>
using namespace std;

SaveAndLoad::SaveAndLoad(Controller& control):control(control){};


void SaveAndLoad::getStateLetter(Player& player, char stateLetter){
    switch(stateLetter){
    case 'N':
        player.state = nullptr;
    case 'P':
        player.state = new HurtPlayer;
        break;
    case 'E':
        player.state = new HurtEnemy;
        break;
    case 'K':
        player.state = new KillEnemy;
        break;
    default:
        throw SaveException("Wrong letter of State");
        break;
    }
}

void SaveAndLoad::strategyLetter(Player& player, char stateLetter){
    switch(stateLetter){
    case 'N':
        player.setStrategy(nullptr);
        break;
    case 'W':
        player.setStrategy(new WeaponStrategy);
        break;
    case 'V':
        player.setStrategy(new VortexStrategy);
        break;
    case 'C':
        player.setStrategy(new CoinStrategy);
        break;
    case 'X':
        player.setStrategy(new ExitStrategy);
        break;
    case 'S':
        player.setStrategy(new WallStrategy);
        break;
    default:
       throw SaveException("Wrong letter of Strategy");
        break;
    }
}

void SaveAndLoad::saveGame(){
            fstream file("/Users/elizaveta/save.txt");
            if (!file.is_open())
                  throw SaveException("Wrong file");

             Player &player = control.getPlayer();
             int info = player.getCoins();   //coins
             file.write((char*)&(info), sizeof(int));
             file << '\n';

             int lives = player.getLives();          //lives
             file.write((char*)&lives, sizeof(int));
             file << '\n';

             int weapon = player.getWeapon();         //weapon
             file.write((char*)&weapon, sizeof(int));
             file << '\n';

             int vortexes = player.vortexes();          //vortex
             file.write((char*)&vortexes, sizeof(int));
             file << '\n';

             int win = player.isWinner();         //win
             file.write((char*)&win, sizeof(int));

             Coords c = player.getCoords();     //Coords
             file.write((char*)&c, sizeof(Coords));

             char stateLetter;

             EnemyState* state = player.getState();   //state
             if (!state)
                 stateLetter = 'N';

             else{
             auto &type = state->getTypeState();
             if (type == typeid(HurtPlayer))
                 stateLetter = 'P';
             else if (type == typeid(HurtEnemy))
                 stateLetter = 'E';
             if (type == typeid(KillEnemy))
                 stateLetter = 'K';
             }

             file << stateLetter;

             PlayerStrategy* strategy = player.getStrategy();
             if (!strategy)
                 stateLetter = 'N';

             else{
             auto &type = strategy->getStrategyType();
             if (type == typeid(WeaponStrategy))
                 stateLetter = 'W';
             else if (type == typeid(VortexStrategy))
                 stateLetter = 'V';
             else if (type == typeid(CoinStrategy))
                 stateLetter = 'C';
             else if (type == typeid(ExitStrategy))
                 stateLetter = 'X';
             if (type == typeid(WallStrategy))
                 stateLetter = 'S';
             }

             file << stateLetter;
                     //ИГРОКА СЧИТАЛИ

             std::list<AbstractEnemy*> &enemies= control.getEnemies();
             int size = enemies.size();
             file.write((char*)&size, sizeof(int));                 //размер списка

             Coords coords;
             for (auto &enemy : enemies) {
                 coords = enemy->getCoords();
                 file.write((char*)&coords, sizeof(Coords));    //   записываем координаты врагов
                 auto &type = enemy->getEnemyType();
                 if (type == typeid(Enemy<TheftBehavior>))
                         stateLetter = 'T';
                 else if (type == typeid(Enemy<AttackBehavior>))
                         stateLetter = 'A';
                 else
                         stateLetter = 'M';
                    file << stateLetter;
                    file << enemy->getChances();
                  }

                file << '\n';

             Field& field = control.getField();
             Type obj;
             for (int y = 0; y < HEIGHT; y++) {
                 for (int x = 0; x < WIDTH; x++) {
                     obj = field.field[y][x].getType();
                     file.write((char*)&obj, sizeof(Type));
                 }
             }
             file.close();
         }


void SaveAndLoad::loadGame(){
    fstream file("/Users/elizaveta/save.txt");
     if (!file.is_open())
         throw SaveException("Couldn't open the file");

     Player &player = control.getPlayer();
    int parameter;
    file.read((char*)&(parameter), sizeof(int));   //coins
    if (parameter > 8)
        throw SaveException("Wrong size of coins");
    file.get();
    player.coins = parameter;


    file.read((char*)&(parameter), sizeof(int));   //lives
    if (parameter > 10)
        throw SaveException("Wrong size of lives");
    file.get();
    player.lives = parameter;


    file.read((char*)&(parameter), sizeof(int));   //weapon
    if (parameter > 10)
        throw SaveException("Wrong size of weapon");
    file.get();
    player.weapon = parameter;


    file.read((char*)&(parameter), sizeof(int));   //vortex
    if (parameter >= 3)
        throw SaveException("Wrong size of vortexes");
    file.get();
    player.takenVortex = parameter;

    file.read((char*)&(parameter), sizeof(int));   //win
    player.win = parameter;

    Coords c;     //Coords
    file.read((char*)&c, sizeof(Coords));
    if (c.h > 15 || c.w > 15 || c.h < 0 || c.w < 0)
        throw SaveException("Wrong coords");
    Coords old = player.getCoords();
    Field& field = control.getField();
    field.field[old.h][old.w].setType(OPEN,nullptr);


    player.setCoords(c);

    char stateLetter;

    EnemyState* state = player.getState();   //state
    if (!state)
        stateLetter = 'N';

    file >> stateLetter;
    getStateLetter(player, stateLetter);
    file >> stateLetter;
    strategyLetter(player, stateLetter);

    int size;
    file.read((char*)&size, sizeof(int));

     if (size < 0)
        throw SaveException("The size of ENEMIES should be > 0");

    std::list<AbstractEnemy*> &enemies = control.getEnemies();
    enemies.clear();
    Coords coords;
    int chances;

    for (int i = 0; i < size; i++) {
        file.read((char*)&coords, sizeof(Coords));
        file >> stateLetter;
        AbstractEnemy* evil;
        switch(stateLetter){
            case 'T':
                   evil = new Enemy<TheftBehavior>(new TheftBehavior(), coords);
                break;
            case 'A':
                   evil = new Enemy<AttackBehavior>(new AttackBehavior(), coords);
                 break;
             case 'M':
                   evil = new Enemy<StalkerBehavior>(new StalkerBehavior(), coords);
                 break;
             default:
                 throw  SaveException("Wrong letter of enemy behavior");
            }
        file >> chances;
        evil->setChances(chances);
        enemies.push_back(evil);
    }


    file.get();

    Type type;
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
              file.read((char*)&type, sizeof(Type));
                field.field[y][x].setObject(type);
        }
    }

    file.close();
}
