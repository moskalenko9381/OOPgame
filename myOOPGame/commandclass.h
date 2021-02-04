#ifndef COMMANDCLASS_H
#define COMMANDCLASS_H
#include "command.h"

class CommandClass
{
    Command* command;
public:
    CommandClass();
    ~CommandClass();
    void setCommand(Command* command);
};

#endif // COMMANDCLASS_H
