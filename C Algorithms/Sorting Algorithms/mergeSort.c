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
    int arr[] = {3,6,4,3,6,7,2,7,-24,-34,-45,-75,13,-46,324,-234,45,0,32,-324};
    int n = sizeof(arr)/sizeof(int);
    printf("Number of elements: %d\n",n);
    mergeSort(arr, 0, n-1);

    printf("The array after sorting:\n");
    for (int i = 0; i < n; i++){
        printf("%d ",arr[i]);
    }
    printf("\n");
    return 0;
}