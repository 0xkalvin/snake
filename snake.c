#include "snake.h"

Snake *create_snake()
{

    Snake *snake = (Snake *)malloc(sizeof(Snake));

    snake->current_tail_size = 1;
    snake->direction = RIGHT;
    snake->head = NULL;
    snake->tail = (Coordinate **)malloc(MAX_TAIL_SIZE * sizeof(Coordinate *));
    snake->tail[0] = snake->head; // TODO

    return snake;
}

void print_snake(Snake *snake){


    


}
