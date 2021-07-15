#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#define X_SIZE 50
#define Y_SIZE 30

char board[Y_SIZE][X_SIZE] = {' '};

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
            board[i][j] = ' ';
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
        board[y][x] = '@';
        return true;
    }
}

int main()
{
    system("cls");
    initialize_board(' ');
    crate_border('#');
    print_board();
    return 0;
}