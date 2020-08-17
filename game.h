#ifndef GAME_H
#define GAME_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "snake.h"
#include "coordinate.h"
#include "helper.h"

#define WIDTH 80
#define HEIGHT 20

typedef struct Game
{
    int is_over;
    int score;
    Snake* snake;
    Coordinate* fruit;

} Game;

Game* setup_game();
void render_game(Game* game);
void process_input(Game* game);
void update_state(Game* game);

int kbhit(void);
char getch();


#endif