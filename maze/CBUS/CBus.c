#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#define MAX 30

// Literals
int n, maxLoad;
int currentLoad = 0, f = 0, fopt = INT_MAX, cmin = INT_MAX;
int mat[MAX][MAX];
int x[MAX], res[MAX];
bool visited[MAX] = {0};

int min(int a, int b){
    return a < b ? a : b;
}

void input(){
    scanf("%d %d",&n,&maxLoad);
    for (int i = 0; i <= 2*n; i++){
        for (int j = 0; j <= 2*n; j++){
            scanf("%d",&mat[i][j]);
            if (mat[i][j]){
                cmin = min(cmin, mat[i][j]);
            }
        }
    }
    x[0] = 0;
}

bool isValid(int point){
    if (visited[point]) return false;
    if (currentLoad > maxLoad)  return false;
    if (point <= n){
        return !visited[point+n];
    }
    return visited[point-n];
}

void Try(int k){
    for (int point = 1; point <= 2*n; point++){
        if (isValid(point)){
            x[k] = point;
            f += mat[x[k-1]][x[k]];
            visited[point] = true;

            if (f >= fopt){
                f -= mat[x[k-1]][x[k]];
                visited[point] = false;
                continue;
            }

            if (point <= n){
                currentLoad++;
            }else{
                currentLoad--;
            }

            if (k == 2*n){
                int g = f + mat[x[k]][x[0]];
                if (g < fopt){
                    fopt = g;
                    for (int a = 0; a <= 2*n; a++){
                        res[a] = x[a];
                    }
                }
            }else{
                int g = f + cmin * (2*n - k + 2);
                if (g < fopt){
                    Try(k+1);
                }
            }

            f -= mat[x[k-1]][x[k]];
            visited[point] = false;
            
            if (point <= n){
                currentLoad--;
            }else{
                currentLoad++;
            }
        }
    }
}

int main(){
    input();
    Try(1);

    printf("The shortest path is: \n");
    for (int i = 0; i <= 2*n; i++){
        printf("%d -> ",res[i]);
    }
    printf("0\n");
    printf("Cost: %d\n",fopt);
    return 0;
}