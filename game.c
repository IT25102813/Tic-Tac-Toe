#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

char board[10][10]; // board[row][col]
FILE *logFile;      // log file

void initialize_board(int size);
void display_board(int size);
void player_move_valid(int *row, int *col, int size, char symbol);
void computer_move_valid(int *row, int *col, int size, char symbol);
bool check_rows_col_diag(char status, int size);
bool check_draw(int size);
int check_winner(char status, int size, int mode);
void show_log_file();

int main() {
    srand(time(NULL));

    int size, mode, row, col;
    char choice;

    logFile = fopen("game_log.txt", "a"); // Open log file to write
    if (!logFile) {
        printf("Error: Could not open log file.\n");
        return 1;
    }

    fprintf(logFile, "\n--- New Game Started ---\n");

    do {
        printf("Enter the board size you want to play (3–10): ");
        scanf("%d", &size);
    } while (size < 3 || size > 10);

    do {
        printf("Enter the mode you want to play\n"
               "1. Player vs Player\n"
               "2. Player vs Computer\n"
               "3. Player vs Player vs Computer\n"
               "4. Player vs Computer vs Computer\n"
               "Mode: ");
        scanf("%d", &mode);
    } while (mode < 1 || mode > 4);

    fprintf(logFile, "Game mode selected: %d\n", mode);

    initialize_board(size);
    display_board(size);

    // Game loop
    for (int turn = 0; turn < size * size; turn++) {
        switch (mode) {
            case 1: // Player vs Player
                player_move_valid(&row, &col, size, 'X');
                board[row][col] = 'X';
                fprintf(logFile, "Player 1 placed X at [%d,%d]\n", row + 1, col + 1);
                display_board(size);
                if (check_winner('X', size, mode) || check_draw(size)) goto end_game;

                player_move_valid(&row, &col, size, 'O');
                board[row][col] = 'O';
                fprintf(logFile, "Player 2 placed O at [%d,%d]\n", row + 1, col + 1);
                display_board(size);
                if (check_winner('O', size, mode) || check_draw(size)) goto end_game;
                break;

            case 2: // Player vs Computer
                player_move_valid(&row, &col, size, 'X');
                board[row][col] = 'X';
                fprintf(logFile, "Player placed X at [%d,%d]\n", row + 1, col + 1);
                display_board(size);
                if (check_winner('X', size, mode) || check_draw(size)) goto end_game;

                computer_move_valid(&row, &col, size, 'O');
                board[row][col] = 'O';
                fprintf(logFile, "Computer placed O at [%d,%d]\n", row + 1, col + 1);
                display_board(size);
                if (check_winner('O', size, mode) || check_draw(size)) goto end_game;
                break;

            case 3: // Player vs Player vs Computer
                player_move_valid(&row, &col, size, 'X');
                board[row][col] = 'X';
                fprintf(logFile, "Player 1 placed X at [%d,%d]\n", row + 1, col + 1);
                display_board(size);
                if (check_winner('X', size, mode) || check_draw(size)) goto end_game;

                player_move_valid(&row, &col, size, 'O');
                board[row][col] = 'O';
                fprintf(logFile, "Player 2 placed O at [%d,%d]\n", row + 1, col + 1);
                display_board(size);
                if (check_winner('O', size, mode) || check_draw(size)) goto end_game;

                computer_move_valid(&row, &col, size, 'C');
                board[row][col] = 'C';
                fprintf(logFile, "Computer placed C at [%d,%d]\n", row + 1, col + 1);
                display_board(size);
                if (check_winner('C', size, mode) || check_draw(size)) goto end_game;
                break;

            case 4: // Player vs Computer vs Computer
                player_move_valid(&row, &col, size, 'X');
                board[row][col] = 'X';
                fprintf(logFile, "Player placed X at [%d,%d]\n", row + 1, col + 1);
                display_board(size);
                if (check_winner('X', size, mode) || check_draw(size)) goto end_game;

                computer_move_valid(&row, &col, size, 'O');
                board[row][col] = 'O';
                fprintf(logFile, "Computer 1 placed O at [%d,%d]\n", row + 1, col + 1);
                display_board(size);
                if (check_winner('O', size, mode) || check_draw(size)) goto end_game;

                computer_move_valid(&row, &col, size, 'C');
                board[row][col] = 'C';
                fprintf(logFile, "Computer 2 placed C at [%d,%d]\n", row + 1, col + 1);
                display_board(size);
                if (check_winner('C', size, mode) || check_draw(size)) goto end_game;
                break;
        }
    }

end_game:
    fclose(logFile);

    printf("\nGame Over! Press 'Q' to view the game log, or any other key to exit: ");
    scanf(" %c", &choice);
    if (choice == 'Q' || choice == 'q') {
        show_log_file();
    }

    printf("\nThanks for playing!\n");
    return 0;
}


void initialize_board(int size) {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            board[i][j] = ' ';
}

void display_board(int size) {
    printf("\n   ");
    for (int j = 0; j < size; j++)
        printf(" %d  ", j + 1);
    printf("\n");

    for (int i = 0; i < size; i++) {
        printf(" %d ", i + 1);
        for (int j = 0; j < size; j++) {
            printf(" %c ", board[i][j]);
            if (j < size - 1) printf("|");
        }
        printf("\n");
        if (i < size - 1) {
            printf("   ");
            for (int j = 0; j < size; j++) {
                printf("---");
                if (j < size - 1) printf("+");
            }
            printf("\n");
        }
    }
    printf("\n");
}

void player_move_valid(int *row, int *col, int size, char symbol) {
    int r, c;
    do {
        printf("Enter your move for '%c' (row column): ", symbol);
        scanf("%d %d", &r, &c);
        r--; c--;
    } while (r < 0 || r >= size || c < 0 || c >= size || board[r][c] != ' ');
    *row = r;
    *col = c;
}

void computer_move_valid(int *row, int *col, int size, char symbol) {
    do {
        *row = rand() % size;
        *col = rand() % size;
    } while (board[*row][*col] != ' ');
    printf("Computer (%c) moved at [%d,%d]\n", symbol, *row + 1, *col + 1);
}

bool check_rows_col_diag(char status, int size) {
    for (int i = 0; i < size; i++) {
        bool row_win = true, col_win = true;
        for (int j = 0; j < size; j++) {
            if (board[i][j] != status) row_win = false;
            if (board[j][i] != status) col_win = false;
        }
        if (row_win || col_win) return true;
    }

    bool diag1 = true, diag2 = true;
    for (int i = 0; i < size; i++) {
        if (board[i][i] != status) diag1 = false;
        if (board[i][size - 1 - i] != status) diag2 = false;
    }
    return diag1 || diag2;
}

int check_winner(char status, int size, int mode) {
    if (check_rows_col_diag(status, size)) {
        switch (status) {
            case 'X': 
                printf("Player 1 wins!\n"); 
                fprintf(logFile, "Player 1 wins!\n"); 
                break;
            case 'O':
                if (mode == 1 || mode == 3) {
                    printf("Player 2 wins!\n"); 
                    fprintf(logFile, "Player 2 wins!\n"); 
                } else {
                    printf("Computer 1 wins!\n"); 
                    fprintf(logFile, "Computer 1 wins!\n"); 
                }
                break;
            case 'C': 
                printf("Computer 2 wins!\n"); 
                fprintf(logFile, "Computer 2 wins!\n"); 
                break;
        }
        return 1;
    }
    return 0;
}

bool check_draw(int size) {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            if (board[i][j] == ' ') return false;

    printf("It's a draw!\n");
    fprintf(logFile, "Game ended in a draw.\n");
    return true;
}

void show_log_file() {
    FILE *file = fopen("game_log.txt", "r");
    if (!file) {
        printf("No log file found.\n");
        return;
    }

    printf("\n========= GAME LOG =========\n");
    char ch;
    while ((ch = fgetc(file)) != EOF) putchar(ch);
    printf("\n============================\n");

    fclose(file);
}

