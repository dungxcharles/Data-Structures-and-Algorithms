#include <stdio.h>
#include <stdlib.h>

void mergeSort(int* arr, int left, int right){
    if (left >= right){
        return;
    }
    int mid = (left + right)/2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid+1, right);

    int tmp[right+1];
    int i = left, j = mid+1, k = 0;
    while (i<=mid && j<=right){
        if (arr[i] < arr[j]){
            tmp[k] = arr[i];
            k++; i++;
        }else{
            tmp[k] = arr[j];
            k++; j++;
        }
    }

    while (i<=mid){
        tmp[k] = arr[i];
        k++; i++;
    }

    while (j<=right){
        tmp[k] = arr[j];
        k++; j++;
    }

    for (int t = left; t <= right; t++){
        arr[t] = tmp[t-left];
    }
}

int main(){
    
    return 0;
}