#ifndef COORDINATE_H
#define COORDINATE_H

#include <stdlib.h>

typedef struct Coordinate
{
    int x, y;
} Coordinate;

Coordinate* create_coordinate(int x, int y);

#endif