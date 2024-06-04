#include <stdio.h>
#include <stdlib.h>

void merge(int *a, int tama, int *b, int tamb)
{
    int *aux = (int *)calloc((tama + tamb), sizeof(int));
    int i = 0;
    int j = 0; 
    int k = 0;
    for (; i < tama && j < tamb; k++)
    {
        if (a[i] <= b[j])
            aux[k] = a[i++];
        else
            aux[k] = b[j++];
    }

    while (i < tama)
        aux[k++] = a[i++];
    while (j < tamb)
        aux[k++] = b[j++];

    for (k = 0, i = 0; i < (tama + tamb); i++, k++)
        a[i] = aux[k];

    free(aux);
}
int v1[900000], v2[200000];

int main() {
    int tama = 0;
    int i = 0;
    while(i<8){
        int tamb = 0;
        scanf(" %d", &tamb);
        for (int j = 0; j < tamb; j++)
            scanf(" %d", &v2[j]);
        merge(v1, tama, v2, tamb);
        tama += tamb;
    i++;
    }

    for (int i = 0; i < tama; i++) {
        printf("%d", v1[i]);
        if (i != tama - 1) {
            printf(" ");
        } else {
            printf("\n");
        }
    }

    return 0;
}
