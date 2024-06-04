#include <stdio.h>
#include <stdlib.h>

// Função que intercala dois vetores ordenados, retornando um vetor união ordenado
int merge2(int *v1, int size_v1, int *v2, int size_v2) {
    int
    i = 0, 
    j = 0, 
    k = 0,
    *w = (int *)malloc((size_v1 + size_v2) * sizeof(int));
    if (w == NULL)
        return 1;

    while (i < size_v1 && j < size_v2) {
        if (v1[i] < v2[j])
            w[k++] = v1[i++];
        else
            w[k++] = v2[j++];
    }
    while (i < size_v1)
        w[k++] = v1[i++];
    while (j < size_v2)
        w[k++] = v2[j++];

    // ao final, anexa o vetor intercalado de v1 e v2, em v1
    for (k = 0, i = 0; i < (size_v1 + size_v2); i++, k++)
        v1[i] = w[k];

    //liberar memoria do vetor auxiliar(w) e de v2;
    free(v2);
    free(w);
    return 0;
}


int intercala8(){
    int   //segundo o problema, o máximo é: 8 * 10^5 = 800.000
    *vec_final = malloc(800000 * sizeof(*vec_final)), size = 0,
    local_size, *local_vec,
    i = 8, j = 0;

    if(vec_final == NULL){
        printf("Alocation Error.\n");
        return 1;
    }
    // a ideia é ele ir comparando incrementalmente cada vetor
    while(i > 0){
        scanf("%d", &local_size);
        // alocando vetor local
        local_vec = malloc(local_size * sizeof(*local_vec));
        for(j = 0; j < local_size; j++)
            scanf("%d ", &local_vec[j]);
        // local_size é liberado da memória ao final de merge2
        if(merge2(vec_final, size, local_vec, local_size))
            return 1;
        size += local_size;
        i--;
    }

    for(i = 0; i < size; i++){
        if(i == size-1)
            printf("%d", vec_final[i]);
        else
            printf("%d ", vec_final[i]);
    }

    free(vec_final);
    return 0;
}

/*

        A ideia é buscar cada um dos vetores localmente ordenados,
    armazená-los em um vetor maior e, para definir seus tamanhos,
    colocar em um vetor de tamanhos, referindo respectivamente aos
    seus intervalos dentro do vetor maior. Desse modo, é possível
    fazer o intercala2 tomando dois-a-dois até alcançar o intercala8.

*/

int main(){
    return intercala8();
}