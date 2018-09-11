#include <stdio.h>

void compAndSwap(int a[], int i, int j, int dir) {
    if (dir == (a[i]>a[j]))
    {
        //swap(a[i],a[j]);
        int aux = a[i];
        a[i] = a[j];
        a[j] = aux;
    }
}

void bitonicMerge(int a[], int low, int cnt, int dir) {
    if (cnt>1) {
        int k = cnt/2;
        int i;
        
        for (i=low; i<low+k; i++)
            compAndSwap(a, i, i+k, dir);
            
        bitonicMerge(a, low, k, dir);
        bitonicMerge(a, low+k, k, dir);
    }
}

void bitonicSort(int a[],int low, int cnt, int dir) {
    if (cnt>1) {
        int k = cnt / 2;
        
        bitonicSort (a, low, k, 1); // ordenar ascendente, pois dir vale 1
        bitonicSort (a, low+k, k, 0); // ordenar decrescente, pois dir vale 0
        bitonicMerge(a, low, cnt, dir); // unificar sequencias, desde que dir=1
    }
}

void sort(int a[], int N, int up) {
    bitonicSort(a, 0, N, up);
}

void main() {
    int a[]= {3, 7, 4, 8, 6, 2, 1, 5};
    int N = sizeof(a)/sizeof(a[0]);
    
    sort(a, N, 1); // Se 0, ordena em ordem decrescente!
    
    printf("Sorted array: \n");
    
    int i;
    
    for (i=0; i<N; i++)
        printf("%d ", a[i]);
}