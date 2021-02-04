#ifndef LOGGERHOLDER_H
#define LOGGERHOLDER_H
#include "LoggerNode.h"

class LoggerHolder
{
    LoggerNode* headLog;
    static LoggerHolder* uniqueHolder;
public:
    LoggerHolder(Logger* head = nullptr);
    static void init(Logger* head);
    static LoggerHolder& instance(Logger* head = nullptr);
    static void deleteInstance();
    void pushLog(Logger* add);
    void popLog();
    void write(const std::string &change);
    ~LoggerHolder();
    friend LoggerHolder& operator<<(LoggerHolder &holder, const std::string &change);
    void printType();
};

#endif // LOGGERHOLDER_H
