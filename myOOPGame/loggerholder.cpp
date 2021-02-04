#include "loggerholder.h"

LoggerHolder* LoggerHolder::uniqueHolder = 0;

LoggerHolder& LoggerHolder::instance(Logger* head) {
  if(uniqueHolder == 0)
     uniqueHolder = new LoggerHolder(head);
  return *uniqueHolder;
}

void LoggerHolder::deleteInstance() {
    delete uniqueHolder;
}

void LoggerHolder::init(Logger* head){
    uniqueHolder = &instance(head);
}

LoggerHolder::LoggerHolder(Logger* head){
    headLog = new LoggerNode(head);
    headLog->next = nullptr;
}

void LoggerHolder::pushLog(Logger* add){
    LoggerNode* newNode = new LoggerNode(add);
    LoggerNode* current = headLog;

    while (current->next)
        current = current->next;

    current->next = newNode;
}

void LoggerHolder::popLog(){
    LoggerNode* current = headLog;

    while (current->next)
        current = current->next;

    current = nullptr;
   }

LoggerHolder::~LoggerHolder(){
    while (headLog){
        LoggerNode* tmp = headLog;
        headLog = headLog->next;
        delete tmp;
    }
}

void LoggerHolder::write(const std::string &change) {
     LoggerNode* current = headLog;
    while (current != nullptr){
        current->log->write(change);
        current = current->next;
    }
}

LoggerHolder& operator<<(LoggerHolder& holder, const std::string &change) {
     holder.write(change);
     return holder;
}
