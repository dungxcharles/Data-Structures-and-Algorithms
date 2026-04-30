#include <stdio.h>
#include <stdbool.h>
#define MAX 100

int n, cnt = 0;
int mat[MAX][MAX] = {0};

void input(){
    scanf("%d",&n);
}

bool canPlace(int r, int c){
    // check rows
    int tr = r, tc = c;
    while (tc >= 0){
        if (mat[tr][tc])    return false;
        tc--;
    }

    // check diagonal up-left
    tr = r, tc = c;
    while (tr >= 0 && tc >= 0){
        if (mat[tr][tc])    return false;
        tr--; tc--;
    }

    // check diagonal bottom-left
    tr = r, tc = c;
    while (tr < n && tc >= 0){
        if (mat[tr][tc])    return false;
        tr++; tc--;
    }
    return true;
}

void printSol(){
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            printf("%d ",mat[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void backTracking(int c){
    for (int row = 0; row < n; row++){
        if (canPlace(row, c)){
            mat[row][c] = 1;
            if (c == n-1){
                printSol();
                cnt++;
            }else{
                backTracking(c+1);
            }
            mat[row][c] = 0;
        }
    }
}

int main(){
    input();
    backTracking(0);
    printf("Solution counted: %d", cnt);
    return 0;
}