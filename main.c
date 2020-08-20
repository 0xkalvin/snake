#include "game.h"

int main(void)
{
    Game *game = alloc_game();
    
    initialize_menu(game);

    run_game(game);

    free(game);

    return 0;
}