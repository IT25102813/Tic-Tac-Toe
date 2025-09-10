#include <stdio.h>
#include <stdlib.h>

void moves(){}

void check_win(){}

void check_draw(){}

void print_board(int n){
    int i = 0;
    int j = 0;

    char board[10][10];
    printf("\n");
    for (i = 0; i < n; i++)         //creating the row
    {
        for (j = 0; j < n; j++)
        {
            board[i][j] = ' ';
            printf("%c", board[i][j]);
            if (j < n - 1)          //reducing one so it will place between two columns except the last
            {    
                printf(" | ");      //dividing the columns
            }
        }
        printf("\n");

        if (i < n - 1)              //reducing one to place between two rows except the last
        {   
            for (int k = 0; k < n; k++)
            { 
                printf("--");
                if (k < n - 1)
                {
                    printf("+");
                }
            }
        }
        printf("\n");
    } 

    printf("%c", board[i][j]);
    
}

int main(){
    int n;

    printf("Enter the board size you want to play ");
    scanf("%d", &n);

    print_board(n);
    
    
    return 0;
}