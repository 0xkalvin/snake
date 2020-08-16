#ifndef SNAKE_H
#define SNAKE_H

#include <stdlib.h>
#include <stdio.h>

#include "coordinate.h"

#define MAX_TAIL_SIZE 100

enum {
    UP,
    DOWN,
    RIGHT,
    LEFT
};

typedef struct Snake
{
    Coordinate* head;
    Coordinate** tail;
    int current_tail_size;
    int direction;
    
} Snake;

Snake* create_snake();
void print_snake(Snake* snake);

#endif