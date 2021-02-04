#include "gamecommands.h"

EndGameCommand::EndGameCommand(GameRuller* ruller):gameRuller(ruller){}

void EndGameCommand::execute() const{
    gameRuller->endGame();
}


CreateGameCommand::CreateGameCommand(GameRuller* ruller):gameRuller(ruller){}

void CreateGameCommand::execute() const{
    gameRuller->createGame();
}

StartNewGameCommand::StartNewGameCommand(GameRuller* ruller):gameRuller(ruller){}

void StartNewGameCommand::execute() const{
    gameRuller->startNewGame();
}


LoadGameCommand::LoadGameCommand(GameRuller* ruller):gameRuller(ruller){}

void LoadGameCommand::execute() const{
    gameRuller->loadGame();
}


SaveGameCommand::SaveGameCommand(GameRuller* ruller):gameRuller(ruller){}

void SaveGameCommand::execute() const{
    gameRuller->saveGame();
}
