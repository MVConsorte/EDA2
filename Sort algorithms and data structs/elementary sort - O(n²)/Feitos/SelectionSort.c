#include <stdio.h>
#include <stdlib.h>
#include <time.h>  //importando a biblioteca para medir tempo de execução
#include <math.h>
#include <string.h>

#define VALUE_RANDOM(inferior_limit,superior_limit) (inferior_limit + (rand() % (superior_limit - inferior_limit + 1)))

int *random_vec(int size, int inferior_limit, int superior_limit);
void execution_time(int *v, int size);
void selectionSort(int *vec, int limit_left, int limit_right);
void selectionSort_rec(int *vec, int limit_left, int limit_right);
void swap(int *a, int *b);


// ------------------------- Selection Sort -------------------------- //
void selectionSort(int *vec, int limit_left, int limit_right){
    for(int j = limit_left; j < limit_right; j++){
        int min_index = j;
        for(int k = j+1; k <= limit_right; k++){
            if(vec[min_index] > vec[k])
                min_index = k;
        }
        swap(&vec[j], &vec[min_index]);
    }
}

// esse irá fazer swap somente como o menor valor relativo de cada subvetor
void selectionSort_rec(int *vec, int limit_left, int limit_right){
    if(limit_left < limit_right){
        int min_index = limit_left;
        for(int k = limit_left + 1; k <= limit_right; k++){
            if(vec[min_index] > vec[k])
                min_index = k;
        }
        // Trocar o menor valor encontrado com o primeiro elem do subvetor
        swap(&vec[limit_left], &vec[min_index]);
        // percorrendo cada sub vetor
        selectionSort_rec(vec, limit_left + 1, limit_right);
    }
}

// uma outra possibilidade, mas que custa um pouco a mais que o anterior, pois ele faz swap sempre que limit_left for maior
// swap() = O(3), melhor caso (swap não é acionado), caso medio (O(n/2)*O(3)) = O((3/2)*n), pior caso (O(3*n))
// Essa fução realiza a ordenação sem utilizar um índice mínimo
void selectionSort_rec_no_min_index(int *vec, int limit_left, int limit_right){
    if(limit_left < limit_right){
        for(int k = limit_left + 1; k <= limit_right; k++){
            if(vec[limit_left] > vec[k])
                swap(&vec[limit_left], &vec[k]);
        }
        // percorrendo cada sub vetor
        selectionSort_rec(vec, limit_left + 1, limit_right);
    }
}

/*
Entre as duas versões do algoritmo de ordenação por seleção, a primeira versão, que utiliza um índice para o menor valor (min_index), é mais eficiente. 
Isso ocorre porque ela minimiza o número de operações de troca (swap). No algoritmo de ordenação por seleção, o custo das comparações é geralmente menor 
do que o das trocas, pois as trocas envolvem mais operações de escrita na memória.

A primeira versão realiza uma única troca por iteração do loop externo, após encontrar o menor elemento no subvetor. Isso significa que, para um vetor de
 tamanho n, haverá no máximo n-1 trocas.

A segunda versão, por outro lado, realiza uma troca sempre que encontra um elemento menor do que o elemento na posição limit_left. Isso pode resultar em 
várias trocas desnecessárias e, portanto, mais operações de escrita na memória, tornando-a menos eficiente.
*/

// pensando em evitar troca desnecessária, foi adicionado uma condição (*a != *b)
void swap(int *a, int *b){
    if(*a - *b){
        int temp = *a;
        *a = *b;
        *b = temp;
    }
}

void swap_raw(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

// fazendo os testes, na prática, com o verificador, achou-se uma média de 2,8813 % de diferença
// sem o verificador, achou-se 2,7797. Logo, esse incremento influe em, apenas, 3,53 % da eficiência
// sendo, em última instância, desprezível para o resultado.

//-------------------------||---------------------------------------//

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




void execution_time(int *v, int size){
    int copy[size];
    memcpy(copy,v,sizeof(*v));

    clock_t begin, end;
    double time_spent, time_spent_two;

    begin = clock();    
    selectionSort(v, 0, size-1);
    end = clock();
    time_spent = (double)(end - begin)/CLOCKS_PER_SEC;
    printf("\n\nExecution time: %.4f sec\n\n", time_spent);

    begin = clock(); 
    selectionSort_rec(copy, 0, size-1);
    end = clock();
    time_spent_two = ((double)(end - begin)/CLOCKS_PER_SEC);
    printf("\n\nExecution time: %.4f sec\n\n", time_spent_two);
    
    time_spent = fabs(time_spent - time_spent_two)/time_spent; //erro absoluto
    printf("\n\nAbsolute error between two functions (recursiva x iterativo): %.4f %%\n\n", time_spent*100);
}

// fabsf == abs(float value); fabs == abs(double value); fabsl == abs(long double value);


int main(){
    int *v, size = 500000, inf_limit = -100, sup_limit = 100;
    // função abaixo: opção para input de usuário
    //*v = input_vec(&size);
    // função abaixo: input de um tamanho definido e randomizado
    v = random_vec(size, inf_limit, sup_limit);

    // imprimindo valores antes da ordenação
    //for(int i = 0; i < size; i++)
    //printf("%d ", v[i]);
    //printf("\n\n");
    //for(int i = 0; i < 10;i++)
    execution_time(v, size);
    //selectionSort(v, 0, size-1);
    // imprimindo valores depois da ordenação
    //for(int i = size-1; i > size - 500; i--)
    //printf("%d ", v[i]);

    free(v);
    return 0;
}

/* 
Observação final:

selectionSort (Iterativa):

Vantagens:
    - Simplicidade: É mais fácil de entender e seguir, especialmente para quem está aprendendo.
    - Controle de Memória: Usa menos memória na pilha porque não há chamadas recursivas.
    - Desempenho: Pode ser ligeiramente mais rápida em algumas implementações devido à ausência de overhead de chamadas recursivas.
Desvantagens:
    - Flexibilidade: Menos flexível em termos de design de algoritmo quando comparada com a versão recursiva.
_______________________________________________________________________
selectionSort_rec (Recursiva):

Vantagens:
    - Elegância e Simplicidade: A recursão pode tornar o código mais limpo e fácil de entender, uma vez que você está confortável com o conceito.
    - Divisão do Problema: A recursão é uma abordagem natural para dividir o problema em subproblemas menores.
Desvantagens:
    - Uso de Memória: Usa mais memória na pilha devido às chamadas recursivas, o que pode levar a um estouro de pilha para vetores muito grandes.
    Ainda mais pelo motivo de ser um algoritimo O(n^2).
    - Desempenho: Pode ser mais lenta devido ao overhead de chamadas recursivas.
*/

