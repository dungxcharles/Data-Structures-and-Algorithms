#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define MAX 10003

typedef struct Term{
    int coef;
    int exp;
    struct Term* next;
}Term;

Term* makeTerm(int coef, int exp){
    Term* newTerm = malloc(sizeof(Term));
    newTerm->coef = coef;
    newTerm->exp = exp;
    newTerm->next = NULL;
    return newTerm;
}

Term* poly[MAX];
void init(){
    for (int i = 0; i < MAX; i++){
        poly[i] = NULL;
    }
}

void creatPoly(){}

void addTerm(int id, int coef, int exp){
    Term* newTerm = makeTerm(coef, exp);
    if (!poly[id]){
        poly[id] = newTerm;
        return;
    }

    if (poly[id]->exp < exp){
        newTerm->next = poly[id];
        poly[id] = newTerm;
    }else if (poly[id]->exp == exp){
        poly[id]->coef += coef;
    }else{
        Term* p = poly[id];
        while (p){
            if (p->next!=NULL && p->next->exp < exp){// 
                newTerm->next = p->next;
                p->next = newTerm;
                return;
            }
            if (p->next!=NULL && p->next->exp == exp){
                p->next->coef += coef;
                return;
            }
            if (p->next == NULL && p->exp > exp){
                p->next = newTerm;
                return;
            }
            p = p->next;
        }
    }
}

int evaluatePoly(int id, int variable_value){
    int evalSum = 0;
    Term* p = poly[id];
    while (p){
        evalSum += (p->coef * pow(variable_value, p->exp));
        p=p->next;
    }
    return evalSum;
}

void freeNode(Term* node){
    if (node == NULL)   return;
    freeNode(node->next);
    free(node);
}

void addLast(Term** head, Term** tail, Term* p){
    if (*head == NULL && *tail == NULL){
        *head = *tail = p;
        return;
    }
    (*tail)->next = p;
    (*tail) = p;
}

Term *addPoly(int id1, int id2, int resultId){
    Term *p1 = poly[id1];
    Term *p2 = poly[id2];
    if (poly[resultId]){
        freeNode(poly[resultId]);
        poly[resultId] = NULL;
    }

    Term* tail = NULL;
    while (p1 && p2){
        if (p1->exp > p2->exp){
            Term* p = makeTerm(p1->coef, p1->exp);
            p1 = p1->next;
            addLast(&poly[resultId], &tail, p);
        }else if (p1->exp == p2->exp){
            // Term* p = p1;
            Term* p = makeTerm(p1->coef + p2->coef, p1->exp);
            p1 = p1->next;
            p2 = p2->next;
            addLast(&poly[resultId], &tail, p);
        }else{
            Term* p = makeTerm(p2->coef, p2->exp);
            p2 = p2->next;
            addLast(&poly[resultId], &tail, p);
        }
    }
    if (p1){
        addLast(&poly[resultId], &tail, p1);
    }
    if (p2){
        addLast(&poly[resultId], &tail, p2);
    }
    return poly[resultId];
}

void printPoly(int id){
    if (poly[id]){
        Term* p = poly[id];
        while (p){
            printf("%d %d ",p->coef, p->exp);
            p=p->next;
        }
        printf("\n");
    }
}

void destroyPoly(int id){
    freeNode(poly[id]);
    poly[id] = NULL;
}

void solution(){
    init();
    char cmd[20];
    while (1){
        scanf("%s",cmd);
        if (cmd[0] == '*')  break;
        if (!strcmp(cmd, "Create")){
            int id; scanf("%d",&id);
        }
        else if (!strcmp(cmd, "AddTerm")){
            int id, coef, exp;
            scanf("%d %d %d",&id, &coef, &exp);
            addTerm(id, coef, exp);
        }
        else if (!strcmp(cmd, "EvaluatePoly")){
            int id, value;
            scanf("%d %d",&id, &value);
            printf("%d\n",evaluatePoly(id, value));
        }
        else if (!strcmp(cmd, "AddPoly")){
            int id1, id2, resId;
            scanf("%d %d %d",&id1, &id2, &resId);
            Term* tmp = addPoly(id1, id2, resId);
        }
        else if (!strcmp(cmd, "PrintPoly")){
            int id; scanf("%d",&id);
            printPoly(id);
        }
        else if (!strcmp(cmd, "Destroy")){
            int id; scanf("%d",&id);
            destroyPoly(id);
        }
    }
}

int main(){
    solution();
    return 0;
}