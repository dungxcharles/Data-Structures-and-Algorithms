#include <stdio.h>
#define EPSILON 0.00000001

double f(double x){
    return x*x-2;
}

void bisection_method(double start, double end, double epsilon, double(*func)(double)){
    if (func(start)*func(end) > 0){
        printf("No solution!\n");
        return;
    }

    float b = 0;
    while (1){
        b = (start + end)/2;
        if (func(b) <= epsilon){
            break;
        }
        if (func(start)*func(b) < 0){
            end = b;
        }else{
            start = b;
        }
    }
    
    printf("Solution: %lf\n", b);
}

int main(){

    return 0;
}