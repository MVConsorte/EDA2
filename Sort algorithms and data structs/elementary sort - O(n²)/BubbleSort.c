#include <stdio.h>
#include <stdlib.h>
#include <time.h>  //importando a biblioteca para medir tempo de execução
#include <math.h>
#include <string.h>

// --------------------- macros ---------------------- //
#define VALUE_RANDOM(inferior_limit,superior_limit) (inferior_limit + (rand() % (superior_limit - inferior_limit + 1)))
#define SWAP(a, b) ({ int temp = *(a); *(a) = *(b); *(b) = temp;})// garante que seja executado adequadamente e uma única vez
#define CMP_SWAP(a, b) ((*(a) < *(b)) ? (SWAP(a, b), 1) : 0) // a < b = troca + retorna 1; caso contrario = retorna 0


int *random_vec(int size, int inferior_limit, int superior_limit);
void execution_time(int *v, int size);
void swap(int *a, int *b);
int cmp_swap(int *a, int *b);


// ------------------------- Bubble Sort -------------------------- //
void bubbleSort(int *vec, int left, int right){ //vec = [left...right]
    for(int i = left; i < right; i++){
        int cmp_flag = 0;
        for(int j = left; j < right; j++){
            if(CMP_SWAP(&vec[j+1], &vec[j]))
                cmp_flag = 1;
        }
        if(!cmp_flag)
            return;
    }
}


void bubbleSort_rec(int *vec, int left, int right){
    if(left < right){
        for(int j = left; j < right; j++)
            CMP_SWAP(&vec[j+1], &vec[j]);
        bubbleSort_rec(vec, left, right-1);
    }
}

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

int cmp_swap(int *a, int *b){ // retorno 1 -> era menor e trocou; retorno 0 -> não era menor e não trocou
    if(a < b){
        swap(a,b);
        return 1; 
    }
    return 0;
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
            vec[k] = i;
        return vec;
    
    case 'c':
        // gerar vetor parcialmente ordenado (30%) crescente
        for(int i = 0; i < size; i++)  // gerar vetor ordenado crescente
            vec[i] = inferior_range + i;
        //vec = random_vec(size, inferior_range, superior_range);
        start_elem = vec[0]; //escolhido dentro do range 
        for(int i = ((size-1)/2), k = 0; i < (size * 0.7); i++, k++){ // desornedar 70% do vetor
            int rand_value = VALUE_RANDOM(start_elem-1, superior_range);
            if(rand_value > vec[i] && rand_value < vec[i-1])
                vec[i] = rand_value;
        }
            
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
    int *copy = malloc(size * sizeof(*copy));
    if(copy != NULL)
        memcpy(copy,v,size * sizeof(*v));
    else return;

    clock_t begin, end;
    double time_spent, time_spent_two;

    begin = clock();    
    bubbleSort(v, 0, size-1);
    end = clock();
    time_spent = (double)(end - begin)/CLOCKS_PER_SEC;
    printf("\n\nExecution time: %.4f sec\n\n", time_spent);


    // --------------------------------------------------------------------
    begin = clock(); 
    bubbleSort_rec(copy, 0, size-1);
    end = clock();
    time_spent_two = ((double)(end - begin)/CLOCKS_PER_SEC);
    printf("\n\nExecution time: %.4f sec\n\n", time_spent_two);
    
    for(int i = 0; i < size; i++)
        if(i <= 1000)
            printf("%d ", copy[i]);
    
    time_spent = fabs(time_spent - time_spent_two)/time_spent; //erro absoluto
    printf("\n\nAbsolute error between two functions (recursiva x iterativo): %.4f %%\n\n", time_spent*100);
    free(copy);
}

// fabsf == abs(float value); fabs == abs(double value); fabsl == abs(long double value);


int main(){
    int *v, size = 10000, inf_limit = -100, sup_limit = 100;
    // função abaixo: opção para input de usuário
    //*v = input_vec(&size);
    // função abaixo: input de um tamanho definido e randomizado
    v = ordenate_vec(size, inf_limit, sup_limit,-1);

    // imprimindo valores antes da ordenação
    for(int i = 0; i < size; i++)
        if(i <= 1000)
            printf("%d ", v[i]);
    printf("\n\n");
    //for(int i = 0; i < 10;i++)
    execution_time(v, size);
    printf("\n\n");
    //selectionSort(v, 0, size-1);
    // imprimindo valores depois da ordenação
    //for(int i = size-1; i > size - 500; i--)
    //printf("%d ", v[i]);
    for(int i = 0; i < size; i++)
        if(i <= 1000)
            printf("%d ", v[i]);

    free(v);
    return 0;
}

/* 
    Observações:
    - Tão fácil de implementar quanto os outros algoritimos elementares.
    - Sempre se comportará pior que os demais.
*/

