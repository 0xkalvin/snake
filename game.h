#ifndef GAME_H
#define GAME_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>

#include "snake.h"
#include "coordinate.h"

#define WIDTH 100
#define HEIGHT 30

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