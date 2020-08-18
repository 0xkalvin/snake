#include "game.h"

int main(void)
{
    Game *game = setup_game();
    
    initialize_menu(game);

    run_game(game);

    free(game);

    return 0;
}