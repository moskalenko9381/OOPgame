#ifndef SAVEEXCEPTION_H
#define SAVEEXCEPTION_H
#include <string>
#include <exception> // для std::exception

using namespace std;

class SaveException: public std::exception
{
    string error;
public:
    SaveException(std::string error)
        : error(error){}

    string& getError() {
        return error; }
};


#endif // SAVEEXCEPTION_H
