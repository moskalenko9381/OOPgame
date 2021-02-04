#ifndef FIELD_H
#define FIELD_H
#include "square.h"
#include "exitobjectfactory.h"
#include "wallobjectfactory.h"
#include "vortexobjectfactory.h"
#include "coinobjectfactory.h"

#define HEIGHT 15
#define WIDTH 15

class Square;
class Field;

class SingletonDestroyer
{
  private:
    Field* uniqueInstance;
  public:
    ~SingletonDestroyer();
    void initialize(Field* p);
};

class Field
{

private:
    friend class GameRuller;
    class Iterator;
    Field();
    Field(int height, int width);
    Field(const Field& obj);
    Field(Field&& obj);
    Field& operator=(Field const& obj);
    Field& operator=(Field&& obj);
    ~Field();
    int height;
    int width;
    friend class SingletonDestroyer;
    static Field* uniqueInstance;
    static SingletonDestroyer destroyer;

public:
    static Field& getInstance(int height = HEIGHT, int width = WIDTH);
    Square** field;
    void makeField();

    Iterator begin();
    Iterator end();
};

class Field::Iterator {
   public:

    int currentHeight;
    int currentWidth;

    Iterator(int h, int w);

    bool operator==(const Iterator& other);
    bool operator!=(const Iterator& other);

    Square& operator*();
    Iterator operator++(int);
    Iterator& operator++();
};


#endif // FIELD_H
