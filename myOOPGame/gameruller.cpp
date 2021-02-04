#include "gameruller.h"

GameRuller::GameRuller(Controller* playerControl,  Field* field):
    playerControl(playerControl), field(field){}

void GameRuller::createGame(){
    playerControl->writeMessage("\t\tSTARTING NEW GAME! LIVES: 10, COINS: 0");
    field = &Field::getInstance(HEIGHT,WIDTH);
    field->makeField();
    playerControl->player = Player();
    playerControl->enemies.clear();
    playerControl->makeEnemies();
};


void GameRuller::endGame(){
  playerControl->writeMessage("\t\tENDING THIS GAME. LIVES: " + std::to_string(playerControl->controlLivesPlayer()) +
                              ", COINS: " + std::to_string(playerControl->controlCoinsPlayer()) +
                              ", RESULT: " + (playerControl->playerWin() ? "WINNER" : "LOSER"));
  for (auto i = 0; i < HEIGHT; i++)
       for(auto j = 0; j < WIDTH; j++)
         field->field[i][j].setType(OPEN);
};

void GameRuller::startNewGame(){
    endGame();
    createGame();
};

void GameRuller::loadGame() {
     Controller& k = *playerControl;
     SaveAndLoad* loader = new SaveAndLoad(k);
     try{
        loader->loadGame();
     }
     catch (SaveException &e) {
       playerControl->writeMessage(e.getError());
     }
}

void GameRuller::saveGame() {
    Controller& k = *playerControl;
    SaveAndLoad* saver = new SaveAndLoad(k);
     try {
        saver->saveGame();
     }
    catch (SaveException &e) {
        playerControl->writeMessage(e.getError());
    }
}

GameRuller::~GameRuller(){
    delete playerControl;
}
