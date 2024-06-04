#include <stdio.h>
#include <stdlib.h>
#include <time.h>  //importando a biblioteca para medir tempo de execu��o
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

// esse ir� fazer swap somente como o menor valor relativo de cada subvetor
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
// swap() = O(3), melhor caso (swap n�o � acionado), caso medio (O(n/2)*O(3)) = O((3/2)*n), pior caso (O(3*n))
// Essa fu��o realiza a ordena��o sem utilizar um �ndice m�nimo
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
Entre as duas vers�es do algoritmo de ordena��o por sele��o, a primeira vers�o, que utiliza um �ndice para o menor valor (min_index), � mais eficiente. 
Isso ocorre porque ela minimiza o n�mero de opera��es de troca (swap). No algoritmo de ordena��o por sele��o, o custo das compara��es � geralmente menor 
do que o das trocas, pois as trocas envolvem mais opera��es de escrita na mem�ria.

A primeira vers�o realiza uma �nica troca por itera��o do loop externo, ap�s encontrar o menor elemento no subvetor. Isso significa que, para um vetor de
 tamanho n, haver� no m�ximo n-1 trocas.

A segunda vers�o, por outro lado, realiza uma troca sempre que encontra um elemento menor do que o elemento na posi��o limit_left. Isso pode resultar em 
v�rias trocas desnecess�rias e, portanto, mais opera��es de escrita na mem�ria, tornando-a menos eficiente.
*/

// pensando em evitar troca desnecess�ria, foi adicionado uma condi��o (*a != *b)
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

// fazendo os testes, na pr�tica, com o verificador, achou-se uma m�dia de 2,8813 % de diferen�a
// sem o verificador, achou-se 2,7797. Logo, esse incremento influe em, apenas, 3,53 % da efici�ncia
// sendo, em �ltima inst�ncia, desprez�vel para o resultado.

//-------------------------||---------------------------------------//

int *random_vec(int size, int inferior_limit, int superior_limit){
    // Inicializa o gerador de num pseudo aleatorio com o tempo atual
    srand(time(NULL));
    // alocando mem�ria para vetor randomizado
    int *vec = malloc(size * sizeof(int));
    if(vec == NULL)
        return NULL;
    // gerando n�meros pseudo-aleat�rios
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
    // fun��o abaixo: op��o para input de usu�rio
    //*v = input_vec(&size);
    // fun��o abaixo: input de um tamanho definido e randomizado
    v = random_vec(size, inf_limit, sup_limit);

    // imprimindo valores antes da ordena��o
    //for(int i = 0; i < size; i++)
    //printf("%d ", v[i]);
    //printf("\n\n");
    //for(int i = 0; i < 10;i++)
    execution_time(v, size);
    //selectionSort(v, 0, size-1);
    // imprimindo valores depois da ordena��o
    //for(int i = size-1; i > size - 500; i--)
    //printf("%d ", v[i]);

    free(v);
    return 0;
}

/* 
Observa��o final:

selectionSort (Iterativa):

Vantagens:
    - Simplicidade: � mais f�cil de entender e seguir, especialmente para quem est� aprendendo.
    - Controle de Mem�ria: Usa menos mem�ria na pilha porque n�o h� chamadas recursivas.
    - Desempenho: Pode ser ligeiramente mais r�pida em algumas implementa��es devido � aus�ncia de overhead de chamadas recursivas.
Desvantagens:
    - Flexibilidade: Menos flex�vel em termos de design de algoritmo quando comparada com a vers�o recursiva.
_______________________________________________________________________
selectionSort_rec (Recursiva):

Vantagens:
    - Eleg�ncia e Simplicidade: A recurs�o pode tornar o c�digo mais limpo e f�cil de entender, uma vez que voc� est� confort�vel com o conceito.
    - Divis�o do Problema: A recurs�o � uma abordagem natural para dividir o problema em subproblemas menores.
Desvantagens:
    - Uso de Mem�ria: Usa mais mem�ria na pilha devido �s chamadas recursivas, o que pode levar a um estouro de pilha para vetores muito grandes.
    Ainda mais pelo motivo de ser um algoritimo O(n^2).
    - Desempenho: Pode ser mais lenta devido ao overhead de chamadas recursivas.
*/

