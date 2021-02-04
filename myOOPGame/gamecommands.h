#ifndef ENDGAMECOMMAND_H
#define ENDGAMECOMMAND_H
#include "command.h"
#include "gameruller.h"

class EndGameCommand: public Command
{
    GameRuller* gameRuller;
public:
    EndGameCommand(GameRuller* ruller);
    void execute() const override;
};


class CreateGameCommand: public Command
{
    GameRuller* gameRuller;
public:
    CreateGameCommand(GameRuller* ruller);
    void execute() const override;
};


class StartNewGameCommand: public Command
{
    GameRuller* gameRuller;
public:
    StartNewGameCommand(GameRuller* ruller);
    void execute() const override;
};

class LoadGameCommand: public Command
{
    GameRuller* gameRuller;
public:
    LoadGameCommand(GameRuller* ruller);
    void execute() const override;
};

class SaveGameCommand: public Command
{
    GameRuller* gameRuller;
public:
    SaveGameCommand(GameRuller* ruller);
    void execute() const override;
};

#endif // ENDGAMECOMMAND_H
