#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

// ------------ MergeSort algorithm -------------------- //

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

// Utilizando o merge para ordenar o vetor inteiro deu: TIME LIMIT EXCEEDED
// ----------------------------------------------------- //

// ------------ QuickSelect algorithm -------------------- //
void troca(int *a, int *b);
int particiona(int *vec, int e, int d);
void quickSelect(int *vec, int e, int d, int k);

void quickSelect(int *vec, int e, int d, int k){
    if(e < d){
        int j = particiona(vec, e, d);
        // --------------- elementos <= pivo
        if(k < j) quickSelect(vec, e, j-1, k);
        // --------------- elementos > pivo
        if(k > j) quickSelect(vec, j+1, d, k);
    }
}

void troca(int *a, int *b){
    int temp = *a; //obtendo valor em 'a'
    *a = *b;
    *b = temp;
}

int particiona(int *vec, int e, int d){
    int p = vec[d], j, k; // p: pivô, j & k: iteradores de comparação com pivo/troca
    for(j = e, k = e; k < d; k++){
        if(vec[k] <= p){
            troca(&vec[k], &vec[j]);
            j++;
        }
    }
    //k == d (pivo), então posiciona p (&vec[d]) em j
    troca(&vec[j], &vec[d]);
    return j;
}


// ----------------------------------------------------- //

int input(){
    int value;
    if(scanf("%d", &value) == 1)
        return value;
    
    return -1;
}


int main(){
    /*
    - N: a quantidade de produtos;
    - P: a página que deve ser apresentada;
    - X: a quantidade de produtos que aparecem por página.
    */
    int *products, N, P, X, i, inf_limit, sup_limit; 
    N = input(); P = input(); X = input();
    products = malloc(N * sizeof(*products));
    
    for(i = 0; i < N; i++)
        products[i] = input();

    // limite inferior da Pagina procurada = (P * X) => primeiro elemento de P na partição de N por X
    inf_limit = P*X;
    // limite superior da Pagina procurada = limite inferior + X
    sup_limit = inf_limit + X;
    
    // em relação ao vetor inteiro
    quickSelect(products, 0, N-1, inf_limit); // encontrou a primeira posição da seção P requerida
    // em relação do vetor[inf_limit + 1 ... N-1], visto que antes de inf_limit todos já são menores que sup_limit
    quickSelect(products, inf_limit + 1, N-1, sup_limit); // encontrou a última posição da seção P requerida

    // ordena no intervalo de 'inf_limit' até 'sup_limit'
    mergeSort(products, inf_limit, sup_limit-1);
    for(i = inf_limit; i < sup_limit; i++)
        if(i < N){
            if(i == sup_limit-1 || i == N-1)
                printf("%d", products[i]);
            else
                printf("%d\n", products[i]);
        }
    return 0;
}


