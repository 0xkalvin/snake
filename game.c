#include "game.h"

Game *setup_game()
{
    srand(time(NULL));

    Game *game = (Game *)malloc(sizeof(Game));

    game->is_over = game->score = 0;

    game->snake = create_snake();

    int snake_head_initial_x = WIDTH / 2;
    int snake_head_initial_y = HEIGHT / 2;
    game->snake->head = create_coordinate(snake_head_initial_x, snake_head_initial_y);

    int fruit_initial_x = abs(rand() % WIDTH - 1);
    int fruit_initial_y = abs(rand() % HEIGHT - 1);

    game->fruit = create_coordinate(fruit_initial_x, fruit_initial_y);

    return game;
}

void initialize_menu(Game *game)
{
    system("clear");

    printf("\n============================== SNAKE GAME =====================================\n\n");
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
                if (game->is_over)
                {
                    printf("%c", 'X');
                }
                else
                {
                    printf("%c", 'O');
                }
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

void update_state(Game *game)
{
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

    /*  Handles fruit collision */
    if (game->fruit->x == game->snake->head->x && game->fruit->y == game->snake->head->y)
    {
        game->fruit->x = abs(rand() % WIDTH - 1);
        game->fruit->y = abs(rand() % HEIGHT - 1);
        game->score += 10;

        game->snake->tail[game->snake->current_tail_size] =
            create_coordinate(0, 0);

        game->snake->current_tail_size++;
    }

    /* Handles collision with its tail  */
    for (int i = 0; i < game->snake->current_tail_size; i++)
    {
        if (game->snake->head->x == game->snake->tail[i]->x && game->snake->head->y == game->snake->tail[i]->y)
        {
            game->is_over = 1;
        }
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