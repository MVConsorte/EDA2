#include <stdio.h>
#include <stdlib.h>

//// MergeSort algorithm  (Estável & O(nlogn)); Contrapartida: Necessita de vetor auxiliar
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

int input(){
    int qtd_elem;
    if(scanf("%d", &qtd_elem) == 1)
        return qtd_elem;
    
    return -1;
}

int main(){
    int *v, i, qtd_elem;
    qtd_elem = input();
    v = malloc(qtd_elem * sizeof(*v));
    
    for(i = 0; i < qtd_elem; i++)
        v[i] = input();
    
    mergeSort(v, 0, qtd_elem-1);
    
    for(i = 0; i < qtd_elem-1; i++)
        printf("%d ",v[i]);
    
    printf("%d\n",v[i]);
        
    return 0;
}