#include "coordinate.h"

Coordinate* create_coordinate(int x, int y){

    Coordinate* coordinate = (Coordinate*)malloc(sizeof(Coordinate));

    coordinate->x = x;
    coordinate->y = y;

    return coordinate;
}