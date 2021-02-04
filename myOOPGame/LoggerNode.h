#ifndef LOGGERNODE_H
#define LOGGERNODE_H
#include "consolelogger.h"
#include "filelogger.h"

class LoggerNode
{
    Logger* log;
    LoggerNode* next;
public:
    friend class LoggerHolder;
    LoggerNode(Logger* l = nullptr, LoggerNode* n = nullptr):log(l),next(n){}
    ~LoggerNode() {
        delete log;
    }
};

#endif // LOGGERNODE_H
