#ifndef COORDINATE_H
#define COORDINATE_H

#include <stdlib.h>

enum {
    EMPTY,
    SNAKE,
    FRUIT
};

typedef struct Coordinate
{
    int x, y, state;
} Coordinate;

Coordinate* create_coordinate(int x, int y, int state);

#endif