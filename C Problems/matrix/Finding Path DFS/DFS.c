#include <stdio.h>
#include <stdbool.h>
#define MAX 1000

typedef struct Pair{
    int x, y;
}Pair;

Pair makePair(int x, int y){
    Pair node; node.x = x; node.y = y;
    return node;
}

// Instances
int cnt = 0;
int n, m, xs, ys, xt, yt;
int maze[MAX][MAX];
Pair parent[MAX][MAX];
int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};

void input(){
    printf("Please input number of rows, number of columns, matrix (0/1), source, target respectively:\n");
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            scanf("%d",&maze[i][j]);
            parent[i][j] = makePair(-1, -1);
        }
    }
    scanf("%d %d %d %d",&xs,&ys,&xt,&yt);
    maze[xs][ys] = 1;
}

bool isValid(Pair node){
    return node.x >= 0 && node.x < n && node.y >= 0 && node.y < m && !maze[node.x][node.y];
}

bool dfs(Pair node){
    if (node.x == xt && node.y == yt){
        return true;
    }
    for (int i = 0; i < 4; i++){
        int x = node.x + dx[i];
        int y = node.y + dy[i];
        Pair child = makePair(x, y);
        if (isValid(child)){
            parent[x][y] = makePair(node.x, node.y);
            maze[x][y] = 1;
            cnt++;
            if (dfs(child)){
                return true;
            }
        }
    }
    return false;
}

void printMaze(){
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            printf("%d ",maze[i][j]);
        }
        printf("\n");
    }
}

void printPath(){
    int x = xt, y = yt;
    while (x != -1 && y != -1){
        maze[x][y] = 2;
        Pair p = parent[x][y];
        x = p.x;
        y = p.y;
    }
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            if (maze[i][j] == 2){
                printf("1 ");
            }else{
                printf("0 ");
            }
        }
        printf("\n");
    }
}

int main(){
    input();
    bool check = dfs(makePair(xs, ys));
    printf("Finding status: %s\n", (check ? "True" : "False"));
    printf("The number of nodes visited: %d\n", cnt);

    if (check){
        printf("Path found by DFS:\n");
        printPath();
    }

    return 0;
}