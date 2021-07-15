#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include <unistd.h>

#define X_SIZE 50
#define Y_SIZE 30
#define DELAY 300000

char board[Y_SIZE][X_SIZE] = {' '};

bool end_game = false;

typedef struct snake_s
{
    uint8_t x_pos;
    uint8_t y_pos;
    struct snake_s *next;
} snake_t;

typedef enum direction_s
{
    LEFT,
    UP,
    RIGHT,
    DOWN
} direction_t;

void initialize_board(char sign)
{
    for(int i = 0; i < Y_SIZE; i++)
    {
        for(int j = 0; j < X_SIZE; j++)
        {
            board[i][j] = sign;
        }
    }
}

void print_board()
{
    system("cls");
    for(int i = 0; i < Y_SIZE; i++)
    {
        for(int j = 0; j < X_SIZE; j++)
        {
            printf("%c", board[i][j]);
        }
        printf("\n");
    }
}

void crate_border(char sign)
{
    for(int i = 0; i < Y_SIZE; i++)
    {
        for(int j = 0; j < X_SIZE; j++)
        {
            if( i == 0 || i == Y_SIZE - 1 ||  j == 0 || j == X_SIZE - 1 )
            {
                board[i][j] = sign;
            }
        }
    }
}

void clear_board(char sign)
{
    for(int i = 1; i < Y_SIZE - 1; i++)
    {
        for(int j = 1; j < X_SIZE - 1; j++)
        {
            board[i][j] = sign;
        }
    }
}

bool add_food(uint8_t x, uint8_t y)
{
    if( x < 1 || x > X_SIZE - 1 || y < 1 || y > Y_SIZE - 1)
    {
        return false;
    }
    else
    {
        board[y][x] = '+';
        return true;
    }
}

snake_t *create_snake()
{
    snake_t *head = NULL;

    head = (snake_t * ) malloc(sizeof(snake_t));

    if(head == NULL)
    {
        return NULL;
    }
    else
    {
        head->x_pos = X_SIZE / 2;
        head->y_pos = Y_SIZE / 2;
        head->next = NULL;
        return head;
    }
}

bool draw_snake(snake_t * snake)
{
    snake_t *tmp = snake;

    if(tmp == NULL)
    {
        return false;
    }
    else
    {      
        board[tmp->y_pos][tmp->x_pos] = 'O';
        tmp = tmp->next;
    }

    while(tmp != NULL)
    {
        board[tmp->y_pos][tmp->x_pos] = 'o';
        tmp = tmp->next;
    }

    return true;
}

bool add_more_snake(snake_t *snake)
{
    if(snake == NULL)
    {
        return false;
    }

    snake_t *tmp = snake;

    while(tmp->next != NULL)
    {
        tmp = tmp->next;
    }

    tmp->next = (snake_t *) malloc(sizeof(snake_t));
    tmp->next->next = NULL;
    tmp->next->x_pos = tmp->x_pos + 1;
    tmp->next->y_pos = tmp->y_pos + 1;

    return true;
}

bool move_snake(snake_t *snake, direction_t dir)
{
    if(snake == NULL)
    {
        return false;
    }

    snake_t *tmp = snake;

    uint8_t temp_x = tmp->x_pos;
    uint8_t temp_y = tmp->y_pos;
    uint8_t temp2_x;
    uint8_t temp2_y;

    switch (dir)
    {
        case LEFT:
            if(tmp->x_pos == 1)
            {
                end_game = true;
                return true;
            }
            tmp->x_pos = tmp->x_pos - 1;
            break;
        
        case UP:
            if(tmp->y_pos == 1)
            {
                end_game = true;
                return true;
            }
            tmp->y_pos = tmp->y_pos - 1;
            break;
        
        case RIGHT:
            if(tmp->x_pos == X_SIZE - 2)
            {
                end_game = true;
                return true;
            }
            tmp->x_pos = tmp->x_pos + 1;
            break;

        case DOWN:
            if(tmp->y_pos == Y_SIZE - 2)
            {
                end_game = true;
                return true;
            }
            tmp->y_pos = tmp->y_pos + 1;
            break;
    }

    tmp = tmp->next;

    while(tmp != NULL)
    {
        temp2_x = tmp->x_pos;
        temp2_y = tmp->y_pos;
        tmp->x_pos = temp_x;
        tmp->y_pos = temp_y;
        temp_x = temp2_x;
        temp_y = temp2_y;
        tmp = tmp->next;
    }

    return true;
}

direction_t keyboard(direction_t dir)
{
    if(kbhit())
    {
        fflush(stdin);
        char key = getch();
        
        if((key == 'w' && dir == DOWN)
            ||(key == 's' && dir == UP)
            ||(key == 'a' && dir == RIGHT)
            ||(key == 'd' && dir == LEFT))
        {
            return dir;
        } 
        switch(key)
        {
            case 'w':
                return UP;
                break;

            case 'a':
                return LEFT;
                break;

            case 'd':
                return RIGHT;
                break;

            case 's':
                return DOWN;
                break;

            case 'q':
                end_game = true;
                return dir;
                break;
        }

    }

    return dir;
}

int main()
{
    initialize_board(' ');
    crate_border('#');
    snake_t *snake =  create_snake();
    add_more_snake(snake);
    add_more_snake(snake);
    add_more_snake(snake);

    draw_snake(snake);
    print_board();
    sleep(2);

    direction_t movement = UP;
    uint16_t score = 0;

    while(true)
    {
        clear_board(' ');
        usleep(DELAY);
        printf("SCORE: %d\n", score);
        movement = keyboard(movement);
        
        move_snake(snake, movement);
        draw_snake(snake);
        print_board();
        if(end_game == true)
        {
            printf("GAME ENDED\n");
            exit(0);
        } 
    }
    
    return 0;
}
