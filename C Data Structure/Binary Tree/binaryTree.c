#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node{
    int val;
    struct Node* left;
    struct Node* right;
}Node;

Node* makeNode(int val){
    Node* p = malloc(sizeof(Node));
    p->val = val;
    p->left = NULL;
    p->right = NULL;
    return p;
}

Node* root;

Node* findNode(int u, Node* r){
    if (r == NULL){
        return NULL;
    }
    if (r->val == u){
        return r;
    }
    Node* findL = findNode(u, r->left);
    if(findL){
        return findL;
    }
    return findNode(u, r->right);
}

void addLeft(int u, int v){
    if (findNode(u, root)){
        return;
    }
    Node* pv = findNode(v, root);
    if (pv && pv->left == NULL){
        Node* pu = makeNode(u);
        pv->left = pu;
    }
}

void addRight(int u, int v){
    if (findNode(u, root)){
        return;
    }
    Node* pv = findNode(v, root);
    if (pv && pv->right == NULL){
        Node* pu = makeNode(u);
        pv->right = pu;
    }
}

void preOrder(Node* r){
    if (r == NULL)  return;
    printf("%d ",r->val);
    preOrder(r->left);
    preOrder(r->right);
}

void inOrder(Node* r){
    if (r == NULL)  return;
    inOrder(r->left);
    printf("%d ",r->val);
    inOrder(r->right);
}

void postOrder(Node* r){
    if (r == NULL)  return;
    postOrder(r->left);
    postOrder(r->right);
    printf("%d ",r->val);
}

void solution(){
    char cmd[100];
    while (1){
        scanf("%s",cmd);
        if (cmd[0] == '*')  break;
        if (!strcmp(cmd, "MakeRoot")){
            int u;
            scanf("%d",&u);
            root = makeNode(u);
        }else if (!strcmp(cmd, "AddLeft")){
            int u, v;
            scanf("%d %d",&u, &v);
            addLeft(u, v);
        }else if (!strcmp(cmd, "AddRight")){
            int u, v;
            scanf("%d %d",&u, &v);
            addRight(u, v);
        }else if (!strcmp(cmd, "PreOrder")){
            preOrder(root);
            printf("\n");
        }else if (!strcmp(cmd, "InOrder")){
            inOrder(root);
            printf("\n");
        }else if (!strcmp(cmd, "PostOrder")){
            postOrder(root);
            printf("\n");
        }
    }
}

int main(){
    solution();
    return 0;
}
