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
    if (r == NULL) return NULL;
    if (r->val == u) return r;
    Node* findL = findNode(u, r->left);
    if (findL) return findL;
    return findNode(u, r->right);
}

Node* findParent(int u, Node* r){
    if (r == NULL) return NULL;
    if ((r->left && r->left->val == u) || (r->right && r->right->val == u))
        return r;
    Node* findL = findParent(u, r->left);
    if (findL) return findL;
    return findParent(u, r->right);
}

void freeTree(Node* r){
    if (r == NULL) return;
    freeTree(r->left);
    freeTree(r->right);
    free(r);
}

/*
 * AddLeft u v:
 *   - Add node u as the left child of v
 *   - If v already has a left child w, then w becomes the left child of u
 *   - Do nothing if u already exists in the tree
 */
void addLeft(int u, int v){
    if (findNode(u, root)) return;
    Node* pv = findNode(v, root);
    if (pv == NULL) return;

    Node* pu = makeNode(u);
    pu->left = pv->left;
    pv->left = pu;
}

/*
 * AddRight u v:
 *   - Add node u as a right child of v
 *   - If v already has a right child w, then w becomes the right child of u
 *   - Do nothing if the u already exists in the tree
 */
void addRight(int u, int v){
    if (findNode(u, root)) return;
    Node* pv = findNode(v, root);
    if (pv == NULL) return;

    Node* pu = makeNode(u);
    pu->right = pv->right;
    pv->right = pu;
}

void removeNode(int u){
    if (root == NULL) return;

    if (root->val == u){
        freeTree(root);
        root = NULL;
        return;
    }

    Node* parent = findParent(u, root);
    if (parent == NULL) return;

    if (parent->left && parent->left->val == u){
        freeTree(parent->left);
        parent->left = NULL;
    } else if (parent->right && parent->right->val == u){
        freeTree(parent->right);
        parent->right = NULL;
    }
}

void preOrder(Node* r){
    if (r == NULL) return;
    printf("%d ", r->val);
    preOrder(r->left);
    preOrder(r->right);
}

void inOrder(Node* r){
    if (r == NULL) return;
    inOrder(r->left);
    printf("%d ", r->val);
    inOrder(r->right);
}

void postOrder(Node* r){
    if (r == NULL) return;
    postOrder(r->left);
    postOrder(r->right);
    printf("%d ", r->val);
}

void solution(){
    char cmd[100];
    while (1){
        scanf("%s", cmd);
        if (cmd[0] == '*') break;

        if (!strcmp(cmd, "MakeRoot")){
            int u;
            scanf("%d", &u);
            root = makeNode(u);
        } else if (!strcmp(cmd, "AddLeft")){
            int u, v;
            scanf("%d %d", &u, &v);
            addLeft(u, v);
        } else if (!strcmp(cmd, "AddRight")){
            int u, v;
            scanf("%d %d", &u, &v);
            addRight(u, v);
        } else if (!strcmp(cmd, "RemoveNode")){
            int u;
            scanf("%d", &u);
            removeNode(u);
        } else if (!strcmp(cmd, "PreOrder")){
            preOrder(root);
            printf("\n");
        } else if (!strcmp(cmd, "InOrder")){
            inOrder(root);
            printf("\n");
        } else if (!strcmp(cmd, "PostOrder")){
            postOrder(root);
            printf("\n");
        }
    }
}

int main(){
    solution();
    return 0;
}