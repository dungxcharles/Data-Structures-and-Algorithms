#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 200                     // In the range of BFS, maze should not be too large

typedef struct Pair{
    int x, y;
}Pair;

typedef struct Node{
    int x, y;
    struct Node* next;
}Node;

// Literals
Node* head = NULL;
Node* tail = NULL;
int n, m, xs, ys, xt, yt;
int maze[MAX][MAX] = {0};
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

Pair parent[MAX][MAX];              // For shortest path finding

Pair makePair(int x, int y){
    Pair newPair; newPair.x = x; newPair.y = y;
    return newPair;
}

Node* makeNode(int x, int y){
    Node* p = malloc(sizeof(Node));
    p->x = x;
    p->y = y;
    p->next = NULL;
    return p;
}

void enqueue(Node* node){
    if (head == NULL){
        head = node;
        tail = node;
        return;
    }
    tail->next = node;
    tail = tail->next;
}

Node* dequeue(){
    if (head == NULL){
        return NULL;
    }
    Node* dequeueNode = head;
    head = head->next;
    if (head == NULL){
        tail = NULL;
    }
    return dequeueNode;
}

bool isEmpty(){
    return head == NULL && tail == NULL;
}

bool isValid(int x, int y){
    return x>=0 && x<n && y>=0 && y<m && maze[x][y]==0;
}

void init(){
    printf("Please input number of rows, number of columns: ");
    scanf("%d %d",&n, &m);

    printf("Please input maze 0/1:\n");
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            scanf("%d",&maze[i][j]);
            parent[i][j] = makePair(-1, -1);
        }
    }

    printf("Please input source position: ");
    scanf("%d %d", &xs, &ys);

    printf("Please input target position: ");
    scanf("%d %d", &xt, &yt);
}

bool bfs(){
    enqueue(makeNode(xs, ys));
    maze[xs][ys] = 1;
    while (!isEmpty()){
        Node* dequeueNode = dequeue();
        for (int i = 0; i < 4; i++){
            int x = dequeueNode->x + dx[i];
            int y = dequeueNode->y + dy[i];
            if (isValid(x, y)){
                maze[x][y] = 1;
                parent[x][y] = makePair(dequeueNode->x, dequeueNode->y);
                if (x == xt && y == yt) return true;
                enqueue(makeNode(x, y));
            }
        }
    }
    return false;
}

void printShortestPath(){
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            maze[i][j] = 0;
        }
    }
    int x = xt, y = yt;
    while (x != -1 && y != -1){
        maze[x][y] = 1;
        int tx = parent[x][y].x;
        int ty = parent[x][y].y;
        x = tx; y = ty;
    }
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            printf("%d ",maze[i][j]);
        }
        printf("\n");
    }
}

int main(){
    init();

    // Early check
    if (xs==xt && ys==yt){
        printf("Status: True - (Source = Target)\n");
        return 0;
    }
    printf("BFS status: ");
    bool checkFlag = bfs();
    if (checkFlag){
        printf("TRUE\n");
    }else{
        printf("FALSE\n");
    }

    if (checkFlag){
        printf("The shortest path:\n");
        printShortestPath();
    }
    return 0;
}