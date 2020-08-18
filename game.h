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

enum {
    WITH_WALLS = 1,
    WITHOUT_WALLS = 2
};

typedef struct Game
{
    int is_over, should_run;
    int score;
    int chosen_mode;
    Snake* snake;
    Coordinate* fruit;

} Game;

Game* setup_game();
void initialize_menu();
void render_game(Game* game);
void render_game_over_screen(Game* game);
void process_input(Game* game);
void update_state(Game* game);
void run_game(Game* game);

#endif