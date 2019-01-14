
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#define EASY 7
#define MEDIUM 15
#define HARD 23
#define NUM_COLUMNS 7
#define NUM_ROWS 7

void printBoard(char board[][7]);
void resetBoard(char board[][7], char userBoard[][7],int checked[][7], int diff);
int inBounds(int i);
void printBoardUser(char board[][7]);
int checkBoard(char gameBoard[][7], char userBoard[][7], int checked[][7], int k, int l);
int splashClear(char gameBoard[][7], char userBoard[][7], int checked[][7], int i, int j);
void clearBoards(int board[][7]);

int main(void){

    char difficulty;
    int difficultySetting;
    char board[NUM_ROWS][NUM_COLUMNS];
    int i, j , k, l;
    char userBoard[NUM_ROWS][NUM_COLUMNS];
    int checked[NUM_ROWS][NUM_COLUMNS];
    int winlose = 0;
    int toWin = NUM_COLUMNS * NUM_ROWS; //number of safe spaces to win

    do{
        printf("\n\n\n\nPlease choose a diffculty: (E)asy/t(M)edium/t(H)ard: ");
        scanf(" %c", &difficulty);

        difficulty = tolower(difficulty);

    }while(!(difficulty == 'e' || difficulty == 'm' || difficulty == 'h'));

    switch(difficulty) {
        case 'e':
            difficultySetting = EASY;
            printf("Difficult set to EASY\n");
            break;
        case 'm':
            difficultySetting = MEDIUM;
            printf("Difficult set to MEDIUM\n");
            break;
        default:
            difficultySetting = HARD;
            printf("Difficult set to HARD\n");
            break;
    }

    //determine how many non Bomb spaces needs to be revealed before win based on difference
    toWin -= difficultySetting;
    resetBoard(board, userBoard, checked, difficultySetting);

    do{
        printBoardUser(userBoard);
        printf("\n");
        printf("Choose a x coordinate: ");
        scanf(" %d", &k);
        printf("Choose a y coordinate: ");
        scanf(" %d", &l);
        printf("X: %d,Y: %d", k,l);
        printf("\n");
        toWin -= checkBoard(board, userBoard, checked, k, l);
        printf("toWin: %d \n", toWin);
    }while(toWin >= 0 );

    printf("\n");
    printBoard(board);
    printf("OUT toWin: %d \n", toWin);
    if(toWin < 0) {
        printf("\nYou LOSE\n");
    }
    else{
        printf("\nYou WIN!\n");
    }
    return(0);
}

void resetBoard(char board[][NUM_COLUMNS], char userBoard[][NUM_COLUMNS], int checked[][NUM_COLUMNS], int diff) {
    int i, j, x, y, hint, testint;
    char temp;
    srand(time(NULL));

    //generate mines
    for(i=0; i<diff;) {
        x = rand() % 7;
        y = rand() % 7;
        if(board[x][y] != 'B'){
            board[x][y] = 'B';
            i++;
        }
    }
    //generate hints
    for(i=0; i<7; i++) {
        for(j=0; j<7; j++){
            //clear out user's game board
            userBoard[i][j] = ' ';
            checked[i][j] = 0;

            hint = 0;
            if (board[i][j] != 'B') {
                //north
                if(inBounds(i+1) == 1)
                    if(board[i+1][j] == 'B')
                        hint++;
                //northeast
                if(inBounds(i+1)== 1 && inBounds(j+1)== 1)
                    if(board[i+1][j+1] == 'B')
                        hint++;
                //northwest
                if(inBounds(i+1)== 1 && inBounds(j-1)== 1)
                    if(board[i+1][j-1] == 'B')
                        hint++;
                //south
                if(inBounds(i-1)== 1)
                    if(board[i-1][j] == 'B')
                        hint++;
                //southeast
                if(inBounds(i-1)== 1 && inBounds(j+1)== 1)
                    if(board[i-1][j+1] == 'B')
                        hint++;
                //southwest
                if(inBounds(i-1)== 1 && inBounds(j-1)== 1)
                    if(board[i-1][j-1] == 'B')
                        hint++;
                //west
                if(inBounds(j-1)== 1)
                    if(board[i][j-1] == 'B')
                        hint++;
                //east
                if(inBounds(j+1)== 1)
                    if(board[i][j+1] == 'B')
                        hint++;

                board[i][j] = hint + '0';
            }

        }
    }
}

void printBoard(char board[][NUM_COLUMNS]) {
    int i=0, j=0, t = 0;

    for(i=0; i<7; i++) {
        for(; t<2; t++) {
            if(t == 0 && i == 0) {
                printf("     ");
                for(j=0; j < 7; j++){
                    printf("(%d)", j);
                }
                printf("\n");
            }
            else {
                printf("     ");
                for(j=0; j < 7; j++){
                    printf(" ^ ");
                }
                printf("\n");
            }
        }
        for(j=0; j<7; j++){
            if (j == 0) {
                printf("(%d)<<", i);
            }
            printf("[%c]",board[i][j]);
            t = 99;
        }
        printf("\n");
    }
}

int inBounds(int i) {
    if(i < 0 | i > 7) {//chekc out of bounds in our matrix
        return 0;
    }
    else {
        return 1;
    }
}
void printBoardUser(char board[][NUM_COLUMNS]) {

    int i, j=0, t = 0, u = 0;
    printf("\n");

    for(i=0; i<7; i++) {
        for(; t<2; t++) {
            if(t == 0 && i == 0) {
                printf("     ");
                for(j=0; j < 7; j++){
                    printf("(%d)", j);
                }
                printf("\n");
            }
            else {
                printf("     ");
                for(j=0; j < 7; j++){
                    printf(" ^ ");
                }
                printf("\n");
            }
        }
        for(j=0; j<7; j++){
            if (j == 0) {
                printf("(%d)<<", i);
            }
            printf("[%c]", board[i][j]);
        }
        printf("\n");
    }
}

int checkBoard(char gameBoard[][NUM_COLUMNS], char userBoard[][NUM_COLUMNS], int checked[][NUM_COLUMNS], int k, int l) {
    if(gameBoard[k][l] == 'B') {
        return 99;
    }
    else if(gameBoard[k][l] == '0') {
        userBoard[k][l] = '0';
        splashClear(gameBoard, userBoard, checked, k, l);
        clearBoards(checked);//clear the array for our checked tracker
        return 1;
    }
    else{
        userBoard[k][l] = gameBoard[k][l];
        return 1;
    }

}

int splashClear(char gameBoard[][NUM_COLUMNS], char userBoard[][NUM_COLUMNS], int checked[][NUM_COLUMNS], int i, int j) {


    if(gameBoard[i][j] == '0' && checked[i][j] != 1 && inBounds(i) && inBounds(j)) {
        checked[i][j] = 1;
        //north
        if(inBounds(i+1) == 1 ){
            splashClear(gameBoard, userBoard, checked, i+1, j);
        }
        //south
        if(inBounds(i-1)== 1){
            splashClear(gameBoard, userBoard, checked, i-1, j);
        }
        //west
        if(inBounds(j-1)== 1){
            splashClear(gameBoard, userBoard, checked, i, j-1);
        }
        //east
        if(inBounds(j+1)== 1) {
            splashClear(gameBoard, userBoard, checked, i, j+1);
        }
        userBoard[i][j] = '0';
        return 1;
    }
    else if (gameBoard[i][j] != 'B') {
        userBoard[i][j] = gameBoard[i][j];
        return 1;
    }
}

void clearBoards(int board[][NUM_COLUMNS]) {
    int x, y;

    for(x = 0; x < 7; x++) {
        for(y = 0; y < 7; y++) {
            board[x][y] = 0;
        }
    }
}
