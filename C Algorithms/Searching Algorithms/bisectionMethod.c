#include <stdio.h>
#include <math.h>
const double EPSILON = 0.00000001;

double f(double x){
    return x*x-2;
}

void bisection_method(double start, double end, double epsilon, double(*func)(double)){
    if (func(start)*func(end) > 0){
        printf("No solution!\n");
        return;
    }

    double b = 0;
    while (1){
        b = (start + end)/2;
        if (fabs(func(b)) <= epsilon){
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
    bisection_method(-1, 5, EPSILON, f);
    return 0;
}