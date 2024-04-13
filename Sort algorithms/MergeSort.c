#include <stdio.h>
#include <stdlib.h>

//// MergeSort algorithm
void intercala(int *v, int e, int m, int d){
    int *w = malloc((d-e+1) * sizeof(int));
    int i = e, j = m+1, k = 0;
    while (i<= m && j <= d){
        if (v[i] < v[j]) w[k++] = v[i++];
        else w[k++] = v[j++];
    }
    while (i <= m) w[k++] = v[i++];
    while (j <= d) w[k++] = v[j++];
    for (k=0, i=e;i <= d; i++, k++) v[i] = w[k];
    free(w);
}

void mergeSort(int *v, int e, int d){
    int m = (d + e)/2;
    if(e < d){
        mergeSort(v, e, m);
        mergeSort(v, m+1, d);
        intercala(v, e, m, d);
    }
}

////  O(nlog(n))