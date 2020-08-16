#include "coordinate.h"

Coordinate* create_coordinate(int x, int y, int state){

    Coordinate* coordinate = (Coordinate*)malloc(sizeof(Coordinate));

    coordinate->x = x;
    coordinate->y = y;
    coordinate->state = state;

    return coordinate;
}