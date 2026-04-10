#include <stdio.h>
#include <stdbool.h>
#define BOARD_SIZE 9

int board[BOARD_SIZE][BOARD_SIZE];
bool isValid(int row, int col, int val){
    // check row
    for (int r = 0; r < BOARD_SIZE; r++){
        if (board[r][col] == val) return false;
    }

    // check col
    for (int c = 0; c < BOARD_SIZE; c++){
        if (board[row][c] == val) return false;
    }

    // check block
    int rowB = row/3 * 3, colB = col/3 * 3;
    for (int i = rowB; i < rowB+3; i++){
        for (int j = colB; j < colB+3; j++){
            if (board[i][j] == val) return false;
        }
    }
    return true;
}

void input(){
    for (int i = 0; i < BOARD_SIZE; i++){
        for (int j = 0; j < BOARD_SIZE; j++){
            scanf("%d",&board[i][j]);
        }
    }
}

void printSolution(){
    for (int i = 0; i < BOARD_SIZE; i++){
        for (int j = 0; j < BOARD_SIZE; j++){
            printf("%d ",board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

bool backTracking(int row, int col){
    if (row == BOARD_SIZE){
        printSolution();
        return true;
    }

    if (col == BOARD_SIZE){
        return backTracking(row+1, 0);
    }

    if (board[row][col]){
        return backTracking(row, col+1);
    }

    for (int v = 1; v <= 9; v++){
        if (isValid(row, col, v)){
            board[row][col] = v;
            if (backTracking(row, col+1)){
                return true;
            }
            board[row][col] = 0;
        }
    }
    return false;
}

int main(){
    printf("Input the sudoku problems:\n");
    input();
    printf("The filled sudoku solution:\n");
    printf("Status: %s", backTracking(0, 0) ? "True" : "False");
    return 0;
}