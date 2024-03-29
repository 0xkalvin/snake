#include "game.h"

int main(void)
{
    Game *game = setup_game();
    
    initialize_menu(game);

    while (!game->is_over)
    {
        render_game(game);
        process_input(game);
        update_state(game);
        usleep(100000);
    }

    free(game);

    return 0;
}