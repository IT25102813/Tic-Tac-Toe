#include <stdio.h>
#include <stdlib.h>

void initial_board(int size){
    int i = 0;
    int j = 0;

    char board[10][10];
    printf("\n");
    for (i = 0; i < size; i++)         //creating the row
    {
        for (j = 0; j < size; j++)
        {
            board[i][j] = ' ';
            printf("%c", board[i][j]);
            if (j < size - 1)          //reducing one so it will place between two columns except the last
            {    
                printf(" | ");      //dividing the columns
            }
        }
        printf("\n");

        if (i < size - 1)              //reducing one to place between two rows except the last
        {   
            for (int k = 0; k < size; k++)
            { 
                printf("---");
                if (k < size - 1)
                {
                    printf("+");
                }
            }
        }
        printf("\n");
    } 

    printf("%c", board[i][j]);
    
}

void display_board(int size){}

void accept_user_input(){}

void validate_user_input(){}

void check_win(){}

void check_draw(){}

int main(){
    int size, 
        play_type,
        end_type,
        winner;

    printf("Enter the board size you want to play ");
    scanf("%d", &size);

    initial_board(size);

    printf("Enter type of play: \nPlayer vs Player: 1\nPlayer vs Computer: 2\nPlayer vs Player vs Computer: 3\n Player vs Computer vs Computer\n");
    scanf("%d", &play_type);

    for (int i = 0; i < size; i++)
    {
        if (play_type == 1)
        {

        }
        else if (play_type == 2)
        {
            
        }
        else if (play_type == 3)
        {
            
        }
        else if (play_type == 4)
        {

        }
    }

    

    return 0;
}