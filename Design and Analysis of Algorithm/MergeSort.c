#include <stdio.h>
#include <stdlib.h>

void merge(int a[], int lb, int mid, int ub) {
    int temp[ub-lb+1]; 
    int i, j, k;
    for(i = lb, j = mid+1, k = 0; i <= mid && j <= ub; ) {
        if(a[i] < a[j]) {
            temp[k++] = a[i++];
        }
        else if(a[i] == a[j]) {
            temp[k++] = a[i++];
            j++;
        }else {
            temp[k++] = a[j++];
        }
    }

    while(i <= mid) temp[k++] = a[i++] ;
    while(j <= ub) temp[k++] = a[j++];
    for(i = lb; i <= ub; i++) {
        a[i] = temp[i-lb];
    }
}

void mergeSort(int a[], int lb, int ub) {
    if(lb < ub) {
        int mid = (lb + ub)/2;
        mergeSort(a, lb, mid);
        mergeSort(a, mid+1, ub);
        merge(a, lb, mid, ub);
    }
}


int main() {

    int a[] = {5,6,1,3,10,9,7,8,2,4};

    mergeSort(a, 0, 9);

    int i;
    for(i = 0; i < 10; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");


    return 0;
}