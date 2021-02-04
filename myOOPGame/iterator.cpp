#include "field.h"

/* Field::Iterator::Iterator(int nowH, int nowW){
    currentHeight = nowH;
    currentWidth = nowW;
    maxHeight = HEIGHT;
   maxWidth = WIDTH;
}

Square Iterator::getNext(){
    if (currentWidth + 1 == maxWidth){
        currentHeight++;
        currentWidth = 0;
    }
    else
        currentWidth++;
        return field[currentHeight][currentWidth];
}

bool Iterator::hasNext(){
    return (currentHeight >= maxHeight - 1 && currentWidth >= maxWidth - 1);
}

bool Iterator::endLine(){
    if(currentWidth == maxWidth-1)
        return true;
    else
        return false;
}

 Field::Iterator Field::begin(){
    return Iterator(0,0);
}

Field::Iterator Field::end(){
    return Iterator(maxHeight-1, maxWidth - 1);
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

Field::Iterator Iterator::operator++(int){
    Iterator iterator(*this);
    if(!hasNext())
        return *this;
    if (currentWidth +1 == maxWidth) {
        currentHeight++;
        currentWidth = 0;
    } else
        currentWidth++;

   operator++();

    return iterator;
} */
