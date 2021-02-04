#include "field.h"

Field *Field::uniqueInstance = nullptr;
SingletonDestroyer Field::destroyer;
const int maxHeight = HEIGHT;
const int maxWidth = WIDTH;

Field::Field() {
    field = nullptr;
}

SingletonDestroyer::~SingletonDestroyer() {
    delete uniqueInstance;
}

void SingletonDestroyer::initialize(Field* p ) {
    uniqueInstance = p;
}

Field& Field::getInstance(int height,int width) {
    if(!uniqueInstance)     {
        uniqueInstance = new Field(height,width);
        destroyer.initialize(uniqueInstance);
    }
    return *uniqueInstance;
}


Field::Field(int height, int width)
{
    this->height = height;
    this->width = width;
    field = new Square*[HEIGHT];

    for (auto i = 0; i < HEIGHT; i++)
        field[i] = new Square[WIDTH];
}


Field::~Field(){
    for (auto i = 0; i < HEIGHT; i++)
       delete[] field[i];
    delete [] field;
}

int mas[HEIGHT][WIDTH] = {
    {0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
    {1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1},
    {1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
    {0, 0, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1},
    {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
    {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1},
    {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1},
    {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
};

void Field::makeField(){
    ExitObjectFactory* exitFactory = new ExitObjectFactory();
    WallObjectFactory* wallFactory = new WallObjectFactory();
    CoinObjectFactory* coinFactory = new CoinObjectFactory();
    VortexObjectFactory* vortexFactory = new VortexObjectFactory();
    WeaponObjectFactory* weaponFactory = new WeaponObjectFactory();

    for(auto i = 0; i < height; i++){
            for(auto j = 0; j < width; j++){
                field[i][j].setH(i);

                if (mas[i][j] == 1)
                       field[i][j].setType(CLOSE, wallFactory->makeObject());

                if (mas[i][j] == 0)
                       field[i][j].setType(OPEN);

                field[i][j].setW(j);
           }
        }
    field[0][0].setType(ENTRY);
    field[HEIGHT-1][WIDTH-1].setType(EXIT, exitFactory->makeObject());


    field[HEIGHT/2][WIDTH/2 +1].setType(COINS, coinFactory->makeObject());
    field[HEIGHT/4 + 1][WIDTH/4].setType(COINS, coinFactory->makeObject());
    field[HEIGHT - 3][WIDTH/2].setType(COINS, coinFactory->makeObject());
    field[HEIGHT-1][1].setType(COINS, coinFactory->makeObject());
    field[1][WIDTH-3].setType(COINS, coinFactory->makeObject());
    field[7][WIDTH-2].setType(COINS, coinFactory->makeObject());
    field[HEIGHT-6][WIDTH/7].setType(COINS, coinFactory->makeObject());
    field[HEIGHT-10][6].setType(COINS, coinFactory->makeObject());

    field[1][2].setType(WEAPON, weaponFactory->makeObject());
    field[0][14].setType(WEAPON, weaponFactory->makeObject());
    field[14][6].setType(WEAPON, weaponFactory->makeObject());
    field[8][11].setType(WEAPON, weaponFactory->makeObject());
    field[4][9].setType(WEAPON, weaponFactory->makeObject());
    field[5][8].setType(WEAPON, weaponFactory->makeObject());
    field[HEIGHT - 5][WIDTH/3].setType(VORTEX, vortexFactory->makeObject());
}


Field::Field(const Field& obj){            //конструктор копирования
    height = obj.height;
    width = obj.width;
    field = new Square*[height];
    for (auto i = 0; i < height; i++){
        field[i] = new Square[width];
        for (auto j = 0; j < width; j++)
            field[i][j] = obj.field[i][j];
    }
}

Field::Field(Field&& obj): height(obj.height), width(obj.width){
    field = obj.field;            //конструктор перемещения
    obj.height = 0;
    obj.width = 0;
    obj.field = nullptr;
}

Field &Field::operator=(Field const& obj){  //оператор присваивания копированием
    if (this != &obj)
        for (auto i = 0; i < height; i++)
            delete [] field[i];
    delete []field;
    height = obj.height;
    width = obj.width;
    field = new Square*[height];
    for (auto i = 0; i < height; i++){
        field[i] = new Square[width];
        for (auto j = 0; j < width; j++)
            field[i][j] = obj.field[i][j];
    }
    return *this;
}


Field& Field::operator=(Field&& obj){  //оператор присваивания перемещением
   if (&obj == this)
    return *this;
   std::swap(height, obj.height);
   std::swap(width, obj.width);
   std::swap(field, obj.field);
   return *this;
}


Field::Iterator::Iterator(int nowH, int nowW){
    currentHeight = nowH;
    currentWidth = nowW;
}

Field::Iterator Field::begin(){
    return Iterator(0,0);
}

Field::Iterator Field::end(){
    return Iterator(maxHeight, 0);
}

Square& Field::Iterator::operator*() {
    return Field::getInstance().field[currentHeight][currentWidth];
}

Field::Iterator& Field::Iterator::operator++(){
    if (currentWidth +1 == maxWidth) {
        currentHeight++;
        currentWidth = 0;
    } else
        currentWidth++;
    return *this;
}

Field::Iterator Field::Iterator::operator++(int){
    Iterator iterator(*this);
    operator++();
    return iterator;
}

bool Field::Iterator::operator==(const Iterator& other) {
    return (currentWidth == other.currentWidth && currentHeight == other.currentHeight);
}

bool Field::Iterator::operator!=(const Iterator& other) {
    return !operator==(other);
}
