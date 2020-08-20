#include "game.h"

Game *alloc_game()
{
    Game *game = (Game *)malloc(sizeof(Game));
    game->should_run = 1;

    return game;
}

void setup_game_initial_state(Game *game)
{
    srand(time(NULL));

    game->is_over = game->score = 0;

    game->snake = create_snake();

    int snake_head_initial_x = WIDTH / 2;
    int snake_head_initial_y = HEIGHT / 2;
    game->snake->head = create_coordinate(snake_head_initial_x, snake_head_initial_y);

    int fruit_initial_x = abs(rand() % WIDTH - 1);
    int fruit_initial_y = abs(rand() % HEIGHT - 1);

    game->fruit = create_coordinate(fruit_initial_x, fruit_initial_y);
}

void initialize_menu(Game *game)
{
    system("clear");

    printf("CHOOSE A MODE TO PLAY\n\n");
    printf("1 - WITH WALLS\n");
    printf("2 - WITH NO WALLS\n");
    printf("3 - QUIT \n\n");

    int valid_option = 0;
    char input_char;

    while (!valid_option)
    {
        scanf("%c", &input_char);

        switch (input_char)
        {

        case '1':
            game->chosen_mode = WITH_WALLS;
            valid_option = 1;
            break;
        case '2':
            game->chosen_mode = WITHOUT_WALLS;
            valid_option = 1;
            break;
        case '3':
            printf("Quitting...\n");
            game->is_over = 1;
            valid_option = 1;
            break;
        default:
            printf("Please, enter a valid mode\n");
            break;
        }
    }
}

void render_game(Game *game)
{

    system("clear");

    printf("\n============================== SNAKE GAME =====================================\n\n");

    printf("\tSCORE %d \n\n", game->score);

    for (int i = 0; i < WIDTH; i++)
    {
        printf("%c", '#');
    }

    printf("\n");

    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            if (game->is_over && i == HEIGHT / 2 && j == WIDTH / 2 - 10)
            {
                render_game_over_screen(game);
            }

            if (j == 0 || j == WIDTH - 1)
            {
                printf("%c", '#');
            }
            else if (game->fruit->x == j && game->fruit->y == i)
            {
                printf("%c", 'F');
            }
            else if (game->snake->head->x == j && game->snake->head->y == i)
            {
                printf("%c", 'O');
            }
            else
            {
                int has_print_snake = 0;

                for (int k = 0; k < game->snake->current_tail_size; k++)
                {
                    if (game->snake->tail[k]->x == j && game->snake->tail[k]->y == i)
                    {
                        printf("%c", 'o');
                        has_print_snake = 1;
                    }
                }
                if (!has_print_snake)
                    printf("%c", ' ');
            }
        }
        printf("\n");
    }

    for (int i = 0; i < WIDTH; i++)
    {
        printf("%c", '#');
    }
}

void render_game_over_screen(Game *game)
{
    
    system("clear");
    
    printf("\n\n\t\t\t\tGAME OVER :(\n\n");

    printf("\n\n\t\tPRESS x TO QUIT OR ANYTHING ELSE TO CONTINUE PLAYING \n\n");


}

void update_state(Game *game)
{
    /*  Handles fruit collision */
    if (game->fruit->x == game->snake->head->x && game->fruit->y == game->snake->head->y)
    {
        game->fruit->x = abs(rand() % WIDTH - 1);
        game->fruit->y = abs(rand() % HEIGHT - 1);
        game->score += 10;

        game->snake->tail[game->snake->current_tail_size] =
            create_coordinate(5, 5);

        game->snake->current_tail_size++;
    }

    /* 
    In case game mode has walls, handles wall collision. 
    Otherwise, snake appears on the other side of the screen
    */
    if (game->chosen_mode == 1)
    {
        if (game->snake->head->x == 0 || game->snake->head->x == WIDTH - 1 ||
            game->snake->head->y < 0 || game->snake->head->y >= HEIGHT)
        {
            game->is_over = 1;
        }
    }
    else
    {

        if (game->snake->head->x == 0)
        {
            game->snake->head->x = WIDTH - 1;
        }
        else if (game->snake->head->x == WIDTH - 1)
        {
            game->snake->head->x = 0;
        }

        if (game->snake->head->y == -1)
        {
            game->snake->head->y = HEIGHT - 1;
        }
        else if (game->snake->head->y == HEIGHT)
        {
            game->snake->head->y = 0;
        }
    }

    /*  Updates tail segments position  */
    Coordinate *previous;

    if (game->snake->tail[0])
    {
        previous = create_coordinate(game->snake->tail[0]->x, game->snake->tail[0]->y);
    }

    game->snake->tail[0] = create_coordinate(game->snake->head->x, game->snake->head->y);

    for (int i = 1; i < game->snake->current_tail_size; i++)
    {

        Coordinate *current = create_coordinate(game->snake->tail[i]->x, game->snake->tail[i]->y);

        game->snake->tail[i]->x = previous->x;
        game->snake->tail[i]->y = previous->y;

        previous->x = current->x;
        previous->y = current->y;
    }

    /*  Updates direction changing */
    switch (game->snake->direction)
    {
    case LEFT:
        game->snake->head->x--;
        break;
    case RIGHT:
        game->snake->head->x++;
        break;
    case UP:
        game->snake->head->y--;
        break;
    case DOWN:
        game->snake->head->y++;
        break;
    }
}

void process_input(Game *game)
{

    if (kbhit())
    {
        char input_char = getch();
        int *direction = &game->snake->direction;

        switch (input_char)
        {

        case 'a':
            *direction = LEFT;
            break;
        case 'd':
            *direction = RIGHT;
            break;
        case 'w':
            *direction = UP;
            break;
        case 's':
            *direction = DOWN;
            break;
        case 'x':
            game->is_over = 1;
            break;
        }
    }
}

int should_keep_running(Game *game)
{
    char input;
    scanf("%c", &input);

    if(input == 'x'){
        return 0;
    }

    return 1;
}

void run_game(Game *game)
{

    setup_game_initial_state(game);

    while (game->should_run)
    {
        while (!game->is_over)
        {
            render_game(game);
            process_input(game);
            update_state(game);
            usleep(100000);
        }

        render_game_over_screen(game);

        if (!should_keep_running(game))
        {
            game->should_run = 0;
        }
        else
        {
            setup_game_initial_state(game);
        }
    }
}