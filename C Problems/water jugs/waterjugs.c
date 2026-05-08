#include <stdio.h>
#include <stdlib.h>
#define MAX 910

int a_level, b_level, target;
int visited[MAX][MAX] = {0};

typedef struct Node{
	int x, y;
	int step;
	struct Node* next;
}Node;

Node* head = NULL;
Node* tail = NULL;

Node* makeNode(int x, int y, int step){
	Node* p = malloc(sizeof(Node));
	p->x = x;
	p->y = y;
	p->step = step;
	p->next = NULL;
	return p;
}

void enqueue(int x, int y, int step){
	Node* newNode = makeNode(x, y, step);
	if (head == NULL && tail == NULL){
		head = tail = newNode;
		return;
	}
	
	tail->next = newNode;
	tail = tail->next;
}

Node* dequeue(){
	if (head == NULL && tail == NULL){
		return NULL;
	}
	Node* res = head;
	head = head->next;
	if (head == NULL){
		tail = NULL;
	}
	return res;
}

void atob(int* x, int* y, int xlevel, int ylevel){
	int tmp = (*y) + (*x);
	if (tmp <= ylevel){
		(*y) += (*x);
		(*x) = 0;
	}else{
		int residual = (*x + *y) - ylevel;
		*y = ylevel;
		*x = residual;
	}
}

int checkSol(int x, int y){
	return x == target || y == target;
}

void operation(int* x, int* y, int xlevel, int ylevel, int opNum){
	if (opNum == 0){
		atob(x, y, xlevel, ylevel);
	}else if (opNum == 1){
		atob(y, x, ylevel, xlevel);
	}else if (opNum == 2){// fill x
		(*x) = xlevel;
	}else if (opNum == 3){// fill y
		(*y) = ylevel;
	}else if (opNum == 4){// empty x
		(*x) = 0;
	}else if (opNum == 5){// empty y
		(*y) = 0;
	}
}

int bfs(){
	enqueue(0, 0, 0);
	visited[0][0] = 1;
	while (head!=NULL){
		Node* tmp = dequeue();
		for (int i = 0; i < 6; i++){
			int x = tmp->x;
			int y = tmp->y;
			int step = tmp->step;
			if (checkSol(x, y)){
				return step;
			}
			operation(&x, &y, a_level, b_level, i);
			if (visited[x][y] == 0){
				visited[x][y] = 1;
				enqueue(x, y, step+1);
			}
		}
	}
	return -1;
}

void input(){
	scanf("%d %d %d",&a_level, &b_level, &target);
}

int main(){
	input();
	printf("%d\n",bfs());
	return 0;
}