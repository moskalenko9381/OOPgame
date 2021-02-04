#ifndef SQUARE_H
#define SQUARE_H
#include <QGraphicsRectItem>
#include "coords.h"
#include "wallobject.h"
#include "exitobject.h"
#include "coinObject.h"
#include "vortexobject.h"

class CellObject;

enum Type{
    CLOSE = 'C', //0 (WALL)
    OPEN  = 'O',  //1
    ENTRY  = 'E', //2
    EXIT   = 'X',//3
    COINS  = 'M', //4
    PLAYER  = 'P', //5
    VORTEX  = 'V',
    WEAPON  = 'W'//6
};

class Square
{
  //  Q_OBJECT
    Type type;
    Coords coords;
    CellObject* object;

public:
     Square(Type type = CLOSE, CellObject* object = nullptr):type(type), object(object){};
     void setType(Type type, CellObject* obj = nullptr);

     Type getType();
     void setDestroyed();

     Coords getCoords();
     CellObject* getObject();

     void setObject(Type t);
     void setH(int h);
     void setW(int w);
};

#endif // SQUARE_H
