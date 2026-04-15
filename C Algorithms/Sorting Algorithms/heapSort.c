#include <stdio.h>

void swap(int* a, int* b){
    int t = *a; *a = *b; *b = t;
}

void heapify(int i, int n, int* arr){
    int L = 2*i+1; int R = 2*i+2; int maxIdx = i;
    if (L<n && arr[maxIdx]<arr[L])  maxIdx = L;
    if (R<n && arr[maxIdx]<arr[R])  maxIdx = R;
    if (maxIdx != i){
        swap(&arr[i], &arr[maxIdx]);
        heapify(maxIdx, n, arr);
    }
}

void heapSort(int* arr, int n){
    for (int i = n/2-1; i>=0; i--){
        heapify(i, n, arr);
    }

    for (int i = n; i>0; i--){
        swap(&arr[0], &arr[i-1]);
        heapify(0, i-1, arr);
    }
}

int main(){
    int arr[] = {1,5,2,7,1,-8,-3,-6,0,9,12,-21};
    int n = sizeof(arr)/sizeof(int);
    printf("The number of element is: %d\n",n);

    heapSort(arr, n);
    printf("The array after sorting is:\n");
    for (int i = 0; i < n; i++){
        printf("%d ",arr[i]);
    }
    printf("\n");
    return 0;
}