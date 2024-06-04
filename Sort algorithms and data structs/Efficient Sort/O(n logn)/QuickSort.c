#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>  //importando a biblioteca para medir tempo de execução

#define VALUE_RANDOM(inferior_limit,superior_limit) (inferior_limit + (rand() % (superior_limit - inferior_limit + 1)))


////////////// QuickSort algorithm ///////////
int particiona(int *vec, int e, int d); // return (int) j. --- orena em relação ao pivô
void troca(int *a, int *b);
void quickSort(int *vec, int e, int d);

// algorítimo de partição de Cormen
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

void troca(int *a, int *b){
    int temp = *a; //obtendo valor em 'a'
    *a = *b;
    *b = temp;
}

void quickSort(int *vec, int e, int d){
    if(e < d){
        int j = particiona(vec, e, d);
        // quicksort elementos <= pivo
        quickSort(vec, e, j-1);
        // quicksort elementos > pivo
        quickSort(vec, j+1, d);
    }
}

///// QuickSort "envenenado" (mediana de 3) algoritimo ////////

// --------- "venenos" para quicksort --------- //
void median_of_three(int *vec, int e, int d); // pega tres elementos e e escolhe a sua mediana como pivô
void pivot_random(int *vec, int e, int d);  // escolhe um pivô aleatório
// -------------------------------------------- //
void quickSort_pivot_random(int *vec, int e, int d);
void quickSort_median_of_three(int *vec, int e, int d);
void execution_time(int *v, int size);

void quickSort_pivot_random(int *vec, int e, int d){
    if(e < d){
        pivot_random(vec, e, d);
        int j = particiona(vec, e, d);
        // quicksort elementos <= pivo
        quickSort_pivot_random(vec, e, j-1);
        // quicksort elementos > pivo
        quickSort_pivot_random(vec, j+1, d);
    }
}

void quickSort_median_of_three(int *vec, int e, int d){
    if(e < d){
        median_of_three(vec, e, d);
        int j = particiona(vec, e, d);
        // quicksort elementos <= pivo
        quickSort_median_of_three(vec, e, j-1);
        // quicksort elementos > pivo
        quickSort_median_of_three(vec, j+1, d);
    }
}

void cmpChange(int *elem_a, int *elem_b){
    if(*elem_b < *elem_a) 
        troca(elem_a, elem_b);
}

void median_of_three(int *vec, int e, int d){  // Theta(1)
    troca(&vec[(e+d)/2], &vec[d-1]);
    cmpChange(&vec[e], &vec[d-1]);
    cmpChange(&vec[e], &vec[d]);
    cmpChange(&vec[d-1], &vec[d]);
}

void pivot_random(int *vec, int e, int d){
    srand(time(NULL));
    // aplicar algoritimo de permutação aleatória
    //for(int i = e; i <= d;i++)
        //troca(&vec[VALUE_RANDOM(i,d)], &vec[i]);
    troca(&vec[VALUE_RANDOM(e,d)], &vec[d]);
}
///////////////

int *input_vec(int *size){
    // tam do vetor
    scanf("%d", size);
    // alocando vetor
    int *v = malloc((*size) * sizeof(int));
    
    // indexando valores do vetor
    for(int i = 0; i < (*size); i++)
        scanf("%d", &v[i]);
    
    return v;
}

int *random_vec(int size, int inferior_range, int superior_range){
    // Inicializa o gerador de num pseudo aleatorio com o tempo atual
    srand(time(NULL));
    // alocando memória para vetor randomizado
    int *vec = malloc(size * sizeof(int));
    if(vec == NULL)
        return NULL;
    // gerando números pseudo-aleatórios
    for(int i = 0; i < size; i++)
        vec[i] = VALUE_RANDOM(inferior_range,superior_range);
    
    return vec;
}

// key_agrs: <gera vetor> '0' - com todos elementos iguais;
// '1' - ordenado e crescente; '-1' - ordenado decrescente;
// 'c' - 30% ordenado e crescente; 'd' - 70% ordenado e decrescente;
// deafult - randomizado
int *ordenate_vec(int size, int inferior_range, int superior_range, char key_agrs){
    int *vec = malloc(size * sizeof(int)), start_elem;
    if(vec == NULL)
        {printf("Erro na alocação\n");return NULL;}
    
    switch (key_agrs)
    {
    case 0:
        // gerar vetor com todos elementos iguais
        for(int i = 0; i < size; i++)
            vec[i] = (superior_range + inferior_range)/2;
        return vec;

    case 1:
        // gerar vetor ordenado crescente
        for(int i = 0; i < size; i++)
            vec[i] = inferior_range + i;
        return vec;
    
    case -1:
        // gerar vetor ordenado decrescente
        for(int i = size, k = 0 ; i > 0; i--, k++)
            vec[i] = superior_range - k;
        return vec;
    
    case 'c':
        // gerar vetor parcialmente ordenado (30%) crescente
        vec = random_vec(size, inferior_range, superior_range);
        start_elem = vec[(size-1)/2]; //escolhido dentro do range um elemento qualquer (ex.: central)
        for(int i = ((size-1)/2), k = 0; i < (size * 0.3); i++, k++)
            vec[i] = start_elem + k;
        return vec;
    
    case 'd':
        // gerar vetor parcialmente ordenado (70%) decrescente
        vec = random_vec(size, inferior_range, superior_range);
        start_elem = vec[size-1]; //escolhido o último elemento
        for(int i = size-1, k = 0; k < (size * 0.2); i--, k++)
            vec[i] = start_elem - k;
        return vec;

    default:
        // gerar vetor aleatório
        return random_vec(size, inferior_range, superior_range);
    }
}


void execution_time(int *v, int size){
    clock_t begin, end;
    double time_spent;
    // copiando valor de v antes de ser ordenando
    int *copy1_v, *copy2_v; 
    copy1_v = malloc(size * sizeof(int));
    copy2_v = malloc(size * sizeof(int));
    memcpy(copy1_v, v, size * sizeof(int));
    memcpy(copy2_v, v, size * sizeof(int));



    printf("*********** QuickSort mediana de tres **********\n");
    begin = clock();
    quickSort_median_of_three(copy1_v, 0, size-1);
    end = clock();

    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("\n\nExecution time: %f sec\n\n", time_spent);
    free(copy1_v);

    printf("*********** QuickSort pivo aleatorio **********\n");
    begin = clock();
    quickSort_pivot_random(copy2_v, 0, size-1);
    end = clock();

    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("\n\nExecution time: %f sec\n\n", time_spent);
    free(copy2_v);

    printf("*********** QuickSort ingênuo **********\n");
    // inicio do medidor de tempo de execução
    begin = clock();
    //quickSort(v, 0, size-1);
    // fim do medidor
    end = clock();
    //time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    //printf("\n\nExecution time: %f sec\n\n", time_spent);
    free(v);
}

/*
    OBSERVAÇÃO: cuidado com o tamanho do vetor (size):
    {*foi feito 3 teste para cada (até o 10.000.000)}
    quickSort(cru):
        - 10.000 => (0,005 seg; 0,012 seg, 0,008 seg)
        - 100.000 => (0,024 seg; 0,017 seg; 0,039 seg)
        - 1.000.000 => (0,212 seg; 0,211 seg; 0,265 seg)
        - 10.000.000 => (9,115 seg; 11,239 seg; 10,002 seg)
        - 100.000.000 => ---
        - 1.000.000.000 => ---
    
    quickSort(envenenado - pivô aleatório):
        - 10.000 => (0,002 seg; 0.016 seg; 0,001 seg)
        - 100.000 => (0.014 seg; 0.026 seg; 0.012 seg;)
        - 1.000.000 => (0.208 seg; 0.219 seg; 0.203 seg)
        - 10.000.000 => (15.287 seg; 14.219 seg; 14.437 seg)
        - 100.000.000 => ---
        - 1.000.000.000 => --- 
    
    [testes realizados em um i5 - 1 a 1,2 Ghz]
    {OBS.: quando aplicou-se a mediana de três, alcançou-se um resultado pior do que o quickSort(cru).}

    - Algorítimo in-place
    - Estabilidade: não é estável (depende da escolha do pivô)
    - Análise assintótica:
        - Pior caso: 
            + Se o pivo, na ordem, for o último ou o primeiro => O(n^2);
            + sol.: tentar achar um elemento proximo ao central (exemplo de solução: mediana de 3)
        - Na prática: O((d-e)+1).
        - Para uma boa escolha do pivô: torna-se O(mergeSorte/2) => O((n/2)*log(n)).
*/

int main(){
    int *v, size = 1000000, inf_limit = -50000, sup_limit = 50000;
    // função abaixo: opção para input de usuário
    //*v = input_vec(&size);
    
    for(int i = 0; i < 10; i++){
    // função abaixo: input de um tamanho definido e randomizado
    v = ordenate_vec(size, inf_limit, sup_limit,'t');

    // imprimindo valores antes da ordenação
    //for(int i = 0; i < size; i++)
    //    printf("%d ", v[i]);
    
    // Ordenando por quickSort(cru)
    // Ordenando por quickSort(envenenado)
    //printf("quicksort raw: ");
    //execution_time(v, size, 0);

    execution_time(v, size);

    printf("\n\n-----------####################-------------\n\n");
    }

    // imprimindo valores depois da ordenação
    //for(int i = 0; i < size; i++)
    //   printf("%d ", v[i]);

    free(v);
    return 0;
}