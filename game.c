#include "game.h"

Game *setup_game()
{
    srand(time(NULL));

    Game *game = (Game *)malloc(sizeof(Game));

    game->is_over = game->score = 0;

    game->snake = create_snake();

    int snake_head_initial_x = WIDTH / 2;
    int snake_head_initial_y = HEIGHT / 2;
    game->snake->head = create_coordinate(snake_head_initial_x, snake_head_initial_y, SNAKE);

    int fruit_initial_x = abs(rand() % WIDTH - 1);
    int fruit_initial_y = abs(rand() % HEIGHT - 1);

    game->fruit = create_coordinate(fruit_initial_x, fruit_initial_y, FRUIT);

    return game;
}

void render_game(Game *game)
{

    system("clear");

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
                printf("%c", 'O');
            }
            else
            {
                printf("%c", ' ');
            }
        }
        printf("\n");
    }

    for (int i = 0; i < WIDTH; i++)
    {
        printf("%c", '#');
    }

    printf("\n Score %d \n", game->score);
}

void update_state(Game *game)
{

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

    /*  Handles collision */
    if (game->fruit->x == game->snake->head->x && game->fruit->y == game->snake->head->y)
    {
        game->fruit->x  = abs(rand() % WIDTH - 1);
        game->fruit->y = abs(rand() % HEIGHT - 1);
        game->score += 10;
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

int kbhit(void)
{
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF)
    {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}

char getch()
{
    char c;
    system("stty raw");
    c = getchar();
    system("stty sane");
    return (c);
}