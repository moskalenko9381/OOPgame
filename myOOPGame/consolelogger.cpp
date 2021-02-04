#include "consolelogger.h"


ConsoleLogger::ConsoleLogger(){
    output = &std::cout;
    type = 1;
}

void ConsoleLogger::write(const std::string& change)
  {
    *output << change << '\n';
  }


int ConsoleLogger::getTypeLog(){
    return type;
}

