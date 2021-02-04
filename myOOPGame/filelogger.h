#ifndef FILELOGGER_H
#define FILELOGGER_H
#include "logger.h"

class FileLogger: public Logger
{
    std::ofstream* output;
    int type;
public:
    FileLogger(const std::string& filename);
    void write(const std::string& change);
    ~FileLogger();
};

#endif // FILELOGGER_H
