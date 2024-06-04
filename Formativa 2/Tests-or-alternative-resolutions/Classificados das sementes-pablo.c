#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#define less(a, b) (a.valor == b.valor ? a.chave < b.chave : a.valor < b.valor)
#define less2(a, b) (a.chave == b.chave ? a.valor < b.valor : a.chave < b.chave)
#define swap(a, b)  { semente t = a; a = b; b = t; }
#define cmpswap(a, b) if (less(b, a)) swap(a, b)
#define cmpswap2(a, b) if (less2(b, a)) swap(a, b)
#define VALUE_RANDOM(inferior_limit,superior_limit) (inferior_limit + (rand() % (superior_limit - inferior_limit + 1)))

typedef struct {
    long long chave;
    int valor;
} semente;

int partition(semente *v, int l, int r) {
    semente pivot = v[r];
    int j = l;
    for (int k = l; k < r; k++)
        if (less2(v[k], pivot)) {
            swap(v[k], v[j]);
            j++;
        }
    swap(v[j], v[r]);
    return j;
}

int partition_outo(semente *v, int l, int r) {
    semente pivot = v[r];
    int j = l;
    for (int k = l; k < r; k++)
        if (less(v[k], pivot)) {
            swap(v[k], v[j]);
            j++;
        }
    swap(v[j], v[r]);
    return j;
}

void insertionsort(semente *v, int l, int r) {
    for (int i = l + 1, j; i <= r; i++) {
        semente t = v[i];
        for (j = i; j > 0 && less2(t, v[j - 1]); j--)
            v[j] = v[j - 1];
        v[j] = t;
    }
}

void quicksort_normal(semente *v, int l, int r) {
    if (r - l <= 32)
        return;

    semente meio = v[(l + r)/2];
    cmpswap2(meio, v[r]);
    cmpswap2(v[l], meio);
    cmpswap2(v[r], meio);

    int m = partition(v, l, r);
    quicksort_normal(v, l, m - 1);
    quicksort_normal(v, m + 1, r);
}

void quicksort_Otimizando(semente *v, int l, int r) {
    quicksort_normal(v, l, r);
    insertionsort(v, l, r);
}

void quickselect(semente *v, int l, int r, int i) {
    cmpswap(v[(l + r) / 2], v[r]);
    cmpswap(v[l], v[(l + r) / 2]);
    cmpswap(v[r], v[(l + r) / 2]);

    int m = partition_outo(v, l, r);
    if (m > i)
        quickselect(v, l, m - 1, i);
    else if (m < i)
        quickselect(v, m + 1, r, i);
}

semente v[20000000];

// ------------------- parte acrescentada
void input_solution(){
    int p;
    scanf(" %d", &p);
    int k = 0;

    while (scanf(" %lld %d", &v[k].chave, &v[k].valor) == 2) {
        k++;
    }

    quickselect(v, 0, k - 1, p - 1);
    quicksort_Otimizando(v, 0, p - 1);

    for (int i = 0; i < p; i++)
        printf("%lld %d\n", v[i].chave, v[i].valor);
}

semente *worst_vec(int size, int inferior_range, int superior_range){
    // Inicializa o gerador de num pseudo aleatorio com o tempo atual
    srand(time(NULL));
    // alocando memória para vetor randomizado
    semente *vec = malloc(size * sizeof(*vec));
    if(vec == NULL){
        printf("Erro na alocação.\n");
        return NULL;
    }
        
    // gerando vetor
    for(int i = size, k = 0; i > 0; i--, k++){
        vec[k].valor = VALUE_RANDOM(inferior_range,superior_range);
        vec[k].chave = i;
    }
    
    return vec;
}

void solution_without_input(){
    clock_t begin, end;
    double time_spent_1;
    int size = 1000000, k = 10000;
    semente *seeds = worst_vec(size, 0, 1);

    begin = clock();
    // Ordenando somente os top K
    quickselect(seeds, 0, size - 1, k - 1);
    quicksort_Otimizando(seeds, 0, k-1); // 0 e k-1
    end = clock();
    time_spent_1 = (double)(end - begin) / CLOCKS_PER_SEC;

    // Imprimindo os top K sementes
    for (int i = 0; i < k; i++) {
        //printf("%lld %d\n", seeds[i].chave, seeds[i].valor);
    }

    printf("\n\nExecution time: %f sec\n\n", time_spent_1);
    free(seeds);
}

int main() {
    solution_without_input();
    return 0;
}
