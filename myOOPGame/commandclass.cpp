#include "commandclass.h"

CommandClass::CommandClass(){}

void CommandClass::setCommand(Command* command){
    this->command = command;
    command->execute();
}

CommandClass::~CommandClass(){
    delete command;
}
