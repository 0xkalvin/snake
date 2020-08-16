#include "game.h"

int main(void)
{

    Game *game = setup_game();

    while (!game->is_over)
    {
        render_game(game);
        process_input(game);
        update_state(game);
        usleep(100000);
    }

    return 0;
}