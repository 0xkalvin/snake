#include "snake.h"

Snake *create_snake()
{

    Snake *snake = (Snake *)malloc(sizeof(Snake));

    snake->current_tail_size = 0;
    snake->direction = RIGHT;
    snake->head = NULL;
    snake->tail = (Coordinate **)malloc(MAX_TAIL_SIZE * sizeof(Coordinate *));

    for (int i = 0; i < MAX_TAIL_SIZE; i++)
    {
        snake->tail[i] = NULL;
    }
    

    return snake;
}

void print_snake(Snake *snake){


    


}
