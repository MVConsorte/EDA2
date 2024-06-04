#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int i,j;
    double value;
} Problem;

//// MergeSort algorithm  (Estável & O(nlogn)); Contrapartida: Necessita de vetor auxiliar

// modificando para atender o requisito de value double e vetor 'Problem'
void intercala(Problem *v, int e, int m, int d){
    Problem *w = malloc((d-e+1) * sizeof(*w));
    int i = e, j = m+1, k = 0;
    while (i<= m && j <= d){
        if (v[i].value >= v[j].value) w[k++] = v[i++]; // trocando '<' por '>=' deixar em ordem decrescente
        else w[k++] = v[j++];
    }
    while (i <= m) w[k++] = v[i++];
    while (j <= d) w[k++] = v[j++];
    for (k=0, i=e;i <= d; i++, k++) v[i] = w[k];
    free(w);
}

// adaptando o mergeSort e intercala para o problema, vetor de 'Problem'
void mergeSort(Problem *v, int e, int d){
    int m = (d + e)/2;
    if(e < d){
        mergeSort(v, e, m);
        mergeSort(v, m+1, d);
        intercala(v, e, m, d);
    }
}

double input(){
    double qtd_elem;
    if(scanf("%lf", &qtd_elem) == 1)
        return qtd_elem;
    
    return -1;
}

// ----------------------- resolução --------------------- //
void multipleSort(){
    // T: o total de casos de teste
    // M: membros da APC
    // N: problemas
    // Na prática, cada caso T, espera-se uma única linha contendo os N x M problemas
    int k,i,j, T, M, N, qtd_elem, pos_elem;
    Problem *v;
    T = input();

    for(k = 0; k < T; k++){
        M = input();
        N = input();
        qtd_elem = (M * N);
        v = malloc(qtd_elem * sizeof(*v));
        
        for(i = 0; i < M; i++){
            for(j = 0; j < N; j++) {
                pos_elem = (i*N)+j;
                v[pos_elem].i = i+1;
                v[pos_elem].j = j+1;
                v[pos_elem].value = input(); //cada membro(i) tem N problemas(j), totalizando (i x N) + j input's.
            }
        }
        
        mergeSort(v, 0, qtd_elem-1); //em ordem decrescente
        
        for(i = 0; i < qtd_elem-1; i++)
            printf("%d,%d ", v[i].i, v[i].j);

        printf("%d,%d\n",v[i].i, v[i].j);
        free(v);
    }
}


// ------------------------------------------------------- //

int main(){
    
    multipleSort();
    return 0;
}