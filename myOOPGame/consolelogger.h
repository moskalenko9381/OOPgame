#ifndef CONSOLELOGGER_H
#define CONSOLELOGGER_H
#include "logger.h"

class ConsoleLogger: public Logger
{
    std::ostream* output;
    int type;
public:
    ConsoleLogger();
    void write(const std::string& change);
    Logger* getNext();
    int getTypeLog();
};

#endif // CONSOLELOGGER_H
