#include "filelogger.h"

FileLogger::FileLogger(const std::string &filename){
    type = 2;
    output  = new std::ofstream(filename.c_str());
    try{
        if(!output)
              throw "Can't open this file!";
    }
    catch (const char* exception) // обработчик исключений типа const char*
        {
            output->close();
            delete output;
            std::cerr << "Error: " << exception << '\n';
        }
}

void FileLogger::write(const std::string& change){
    if (!output)
        return;

    *output << change << '\n';
}

FileLogger::~FileLogger(){
    output->close();
    delete output;
}

