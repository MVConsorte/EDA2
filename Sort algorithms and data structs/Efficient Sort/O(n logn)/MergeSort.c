#include <stdio.h>
#include <stdlib.h>
#include <time.h>  //importando a biblioteca para medir tempo de execução

#define VALUE_RANDOM(inferior_limit,superior_limit) (inferior_limit + (rand() % (superior_limit - inferior_limit + 1)))

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

int input_vec(int *v){
    int qtd, i;
    // tam do vetor
    scanf("%d", &qtd);
    // alocando vetor
    v = malloc(qtd * sizeof(int));
    
    // indexando valores do vetor
    for(i = 0; i < qtd; i++)
        scanf("%d", &v[i]);
    
    return qtd;
}

int *random_vec(int size, int inferior_limit, int superior_limit){
    // Inicializa o gerador de num pseudo aleatorio com o tempo atual
    srand(time(NULL));
    // alocando memória para vetor randomizado
    int *vec = malloc(size * sizeof(int));
    if(vec == NULL)
        return NULL;
    // gerando números pseudo-aleatórios
    for(int i = 0; i < size; i++)
        vec[i] = VALUE_RANDOM(inferior_limit,superior_limit);
    
    return vec;
}

////  O(nlog(n))

/*
    OBSERVAÇÃO: cuidado com o tamanho do vetor (size):
        - 10.000 => 0,006 seg
        - 100.000 => 0,016 seg
        - 1.000.000 => 0,26 seg
        - 10.000.000 => 3 seg
        - 100.000.000 => 76 seg
        - 1.000.000.000 => 18,5 min 
        {principal motivo, gargalo de memória, leitura e escrita bastante custoso;
        além do que, para essa quantidade de elemntos int => (4 bytes x 1 bi)/2^20 = 3.815 MB ou 3.8 GB}
    
    testes realizados em um i5 - 1 a 1,2 Ghz
*/

int main(){
    //int *vec, i;
    // função abaixo: opção para input de usuário
    //int qtd = input_vec(vec);

    // Inicializa o gerador de num pseudo aleatorio com o tempo atual
    srand(time(NULL));
    int *v, size = 100000; // value = 10.000.000 -> 3 seg; if(value*10) -> 76 seg
    for(int i = 0; i < 3;i++){
    // função abaixo: input de um tamanho definido e randomizado
    v = random_vec(size, -2000000, 5000000);

    // imprimindo valores antes da ordenação
    //for(i = 0; i < size; i++)
    //    printf("%ld ", v[i]);

    // inicio do medidor de tempo de execução
    clock_t begin = clock();
    
    // Ordenando por mergeSort
    mergeSort(v, 0, size-1);
    
    // fim do medidor
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    printf("\n\nExecution time: %f sec\n\n", time_spent);
    }
    

    // imprimindo valores depois da ordenação
    //for(i = 0; i < size; i++)
    //    printf("%ld ", v[i]);

    free(v);
    return 0;
}