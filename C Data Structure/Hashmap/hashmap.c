#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MOD 100007

typedef struct Node{
    int val;
    struct Node* next;
}Node;

Node* makeNode(int val){
    Node* p = malloc(sizeof(Node));
    p->val = val;
    p->next = NULL;
    return p;
}

Node* hashtable[MOD];

void init(){
    for (int i = 0; i < MOD; i++){
        hashtable[i] = NULL;
    }
}

int hash(int val){
    return val%MOD;
}

void put(int val){
    Node* newNode = makeNode(val);
    int idx = hash(val);
    newNode->next = hashtable[idx];
    hashtable[idx] = newNode;
}

bool findNode(int val){
    int idx = hash(val);
    Node* p = hashtable[idx];
    while (p != NULL){
        if (p->val == val){
            return true;
        }
        p = p->next;
    }
    return false;
}

int main(){
    init();
    put(12);
    put(9);
    put(1);
    put(5);
    printf("%d",findNode(1));
    return 0;
}