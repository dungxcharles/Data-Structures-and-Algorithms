#include <stdio.h>
#include <stdbool.h>
#define MAX 20

typedef struct Pair{
    int first, second;
}Pair;

Pair make_pair(int x, int y){
    Pair res; res.first = x; res.second = y;
    return res;
}

int n, H, W;
int material[MAX][MAX] = {0};
int visualization[MAX][MAX] = {0};
Pair rect[MAX];

void swap(int i, int j){
    Pair tmp = rect[i];
    rect[i] = rect[j];
    rect[j] = tmp;
}

double areaOf(Pair rectangle){
    return (double)rectangle.first * rectangle.second;
}

void bubbleSort(){
    for (int i = 0; i < n-1; i++){
        for (int j = 0; j < n-i-1; j++){
            if (areaOf(rect[j]) < areaOf(rect[j+1])){
                swap(j, j+1);
            }
        }
    }
}

void input(){
    scanf("%d %d",&H, &W);
    scanf("%d",&n);
    for (int i = 0; i < n; i++){
        scanf("%d %d",&rect[i].first, &rect[i].second);
    }
    bubbleSort();
}

void printSolution(){
    for (int i = 0; i < H; i++){
        for (int j = 0; j < W; j++){
            printf("%d ",visualization[i][j]);
        }
        printf("\n");
    }
}

bool canPlace(int i, int j, int h, int w){
    if ((i + h > H) || (j + w > W)){
        return false;
    }
    for (int k = i; k < i+h; k++){
        for (int l = j; l < j+w; l++){
            if (material[k][l]){
                return false;
            }
        }
    }
    return true;
}

void place(int i, int j, int h, int w, int val, int idx){
    for (int k = i; k < i+h; k++){
        for (int l = j; l < j+w; l++){
            material[k][l] = val;
            visualization[k][l] = idx+1;
        }
    }
}

bool backTracking(int recIndex){
    if (recIndex == n){
        return true;
    }
    int h = rect[recIndex].first;
    int w = rect[recIndex].second;
    for (int i = 0; i < H; i++){
        for (int j = 0; j < W; j++){
            if (material[i][j] == 0){
                if (canPlace(i, j, h, w)){
                    place(i, j, h, w, 1, recIndex);
                    if (backTracking(recIndex+1)){
                        return true;
                    }
                    place(i, j, h, w, 0, -1);
                }
                if (h != w && canPlace(i, j, w, h)){
                    place(i, j, w, h, 1, recIndex);
                    if (backTracking(recIndex+1)){
                        return true;
                    }
                    place(i, j, w, h, 0, -1);
                }
            }else{
                continue;
            }
        }
    }
    return false;
}

int main(){
    input();
    bool check = backTracking(0);
    printf("Status: %s\n", (check ? "True" : "False"));
    printf("We can arrange as below:\n");
    printSolution();
    return 0;
}