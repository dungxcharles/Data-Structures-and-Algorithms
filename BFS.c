#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int x, y;
    struct Node* next;
}Node;

Node* head = NULL;
Node* tail = NULL;

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
    return dequeueNode;
}

int main(){
    enqueue(makeNode(1,2));
    enqueue(makeNode(2,5));

    dequeue();
    Node* a = dequeue();
    printf("%d %d",a->x, a->y);
    printf("Hello World\n");
    return 0;
}