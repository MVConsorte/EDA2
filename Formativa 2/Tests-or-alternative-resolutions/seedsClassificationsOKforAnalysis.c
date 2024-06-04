#include <stdio.h>
#include <stdlib.h>

#include <time.h>  //importando a biblioteca para medir tempo de execução

#define VALUE_RANDOM(inferior_limit,superior_limit) (inferior_limit + (rand() % (superior_limit - inferior_limit + 1)))


typedef struct{
    int code;
    int score;
} Seed;
// ------------ QuickSelect algorithm for Seed -------------------- //
void troca(Seed *a, Seed *b);
int particiona(Seed *vec, int e, int d,char key);
void cmp_exch(Seed *elem_a, Seed *elem_b);
void median_of_three(Seed *vec, int e, int d);
void quickSelect(Seed *vec, int e, int d, int k, char key); 
void quickSort(Seed *vec, int e, int d, char key);

void quickSort(Seed *vec, int e, int d, char key){
    if(e < d){
        median_of_three(vec, e, d);
        int j = particiona(vec, e, d, key);
        // --------------- elementos <= pivo
        quickSort(vec, e, j-1, key);
        // --------------- elementos > pivo
        quickSort(vec, j+1, d, key);
    }
}

// adaptando o particiona/quicksort: 
// key = 0 => ordenar seed em relação ao score
// key != 0 => ordenar seed em relação ao codigo
void quickSelect(Seed *vec, int e, int d, int k, char key){
    if(e < d){
        median_of_three(vec, e, d);
        int j = particiona(vec, e, d, key);
        // --------------- elementos <= pivo
        if(k < j) quickSelect(vec, e, j-1, k, key);
        // --------------- elementos > pivo
        if(k > j) quickSelect(vec, j+1, d, k, key);
    }
}
void troca(Seed *a, Seed *b){
    Seed temp = *a; //obtendo valor em 'a'
    *a = *b;
    *b = temp;
}
int particiona(Seed *vec, int e, int d, char key){
    int j,k; //j & k: iteradores de comparação com pivo/troca
    Seed p = vec[d]; // p: pivô
    for(j = e, k = e; k < d; k++){
        if(!key){
            // OBS>: Quanto menor o valor da nota de qualidade melhor é a semente.
            if(vec[k].score >= p.score){
                if(vec[k].score == p.score){
                    if(vec[k].code > p.code){
                        troca(&vec[k], &vec[j]);
                        j++;
                    }
                } else {
                    troca(&vec[k], &vec[j]);
                    j++;
                }
            } 
        } else {
            // OBS>: ordenando sentido crescente de código
            if(vec[k].code < p.code){
                troca(&vec[k], &vec[j]);
                j++;
            }
            //printf("k= %d- pivo= %d- j= %d-\n", vec[k].code, p.code, vec[j].code); 
        }
    }
    //k == d (pivo), então posiciona p (&vec[d]) em j
    troca(&vec[j], &vec[d]);
    return j;
}

void cmp_exch(Seed *elem_a, Seed *elem_b){
    // Ordenar decrescente em relação à nota
    if(elem_b->score < elem_a->score)
        troca(elem_b, elem_a);
    else if(elem_b->score == elem_a->score)
        // ordem crescente em relação à código
        if(elem_b->code > elem_a->code)
            troca(elem_b, elem_a);
}

void median_of_three(Seed *vec, int e, int d){  // Theta(1)
    troca(&vec[(e+d)/2], &vec[d-1]);
    cmp_exch(&vec[e], &vec[d-1]);
    cmp_exch(&vec[e], &vec[d]);
    cmp_exch(&vec[d-1], &vec[d]);
}

// ----------------------------------------------------- //
int input(){
    int value, exit = scanf("%d", &value);
    if(exit == 1 || exit != EOF)
        return value;
    else
        return exit;
}


Seed *worst_vec(int size, int inferior_range, int superior_range){
    // Inicializa o gerador de num pseudo aleatorio com o tempo atual
    srand(time(NULL));
    // alocando memória para vetor randomizado
    Seed *vec = malloc(size * sizeof(Seed));
    if(vec == NULL){
        printf("Erro na alocação.\n");
        return NULL;
    }
        
    // gerando vetor
    for(int i = size, k = 0; i > 0; i--, k++){
        vec[k].score = VALUE_RANDOM(inferior_range,superior_range);
        vec[k].code = i;
    }
    
    return vec;
}

void solution_by_input(){
    // k: quantas TOP sementes deverá ser selecionadas
    // max_inputs: 10^7 entradas possíveis para sementes disponibilizada por EDA
    int k, value_temp, size, max_inputs = 10000000, e,d,i;
    Seed *seeds = malloc(max_inputs * sizeof(*seeds));

    k = input(); //referente ao npumero de top seeds
    for(size = 0; size < max_inputs; size++){
        value_temp = input(); //Lendo codigo da seed
        if(value_temp != EOF){
            seeds[size].code = value_temp;  
            value_temp = input(); //Lendo nota da seed 
            if(value_temp != EOF)
                seeds[size].score = value_temp; 
            else
                break;
        }  
        else
            break;
    }

    // definindo index do inicio do vetor e do final, respectivamente
    e = 0; d = size-1, i = k; // armazenando numero de tops em variável temporaria i
    
    // ordenando somente os top K
    for(value_temp = e; k > 0; k--){
        // queremos os TOP's k melhores seeds, o elemento buscado = d-k
        quickSelect(seeds, value_temp, d, size-k,0);
        value_temp = size-k;
        // agr, o novo intervalo é de (d-k)+1 até d, pois antes de (d-k) todos já são menores que k e (d-k) está na posição certa.
        value_temp++; 
    }

    k = i;//retornando valor de i para k
    // printando os top k 
    for(i = 0, value_temp = size-k; i < k; i++, value_temp++){
        //TOP's k melhores seeds, ordenados em sentido crescente de código
        quickSelect(seeds, value_temp, d, value_temp,1);
        if(i == k-1)
            printf("%d %d", seeds[value_temp].code, seeds[value_temp].score);
        else
            printf("%d %d\n",seeds[value_temp].code, seeds[value_temp].score);
    }
    free(seeds);
}

void worst_solution(){
    clock_t begin, end;
    double time_spent_1,time_spent_2;
    int size = 1000000, inferior_range = 0, superior_range = 1, k = 10000;
    Seed *seeds = worst_vec(size, inferior_range, superior_range);

    // ordenando somente os top K
    begin = clock();
    for(int value_temp = 0, k_temp = k; k_temp > 0; k_temp--){
        // queremos os TOP's k melhores seeds, o elemento buscado = d-k
        quickSelect(seeds, value_temp, size-1, size-k_temp,0);
        value_temp = size-k_temp;
        // agr, o novo intervalo é de (d-k)+1 até d, pois antes de (d-k) todos já são menores que k e (d-k) está na posição certa.
        value_temp++; 
    }
    end = clock();
    time_spent_1 = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("\n\nExecution time: %f sec\n\n", time_spent_1);

    
    
    begin = clock();
    // printando os top k 
    for(int value_temp = size-k; value_temp < size; value_temp++){
        //TOP's k melhores seeds, ordenados em sentido crescente de código
        quickSelect(seeds, value_temp, size-1, value_temp,1);
        if(value_temp == size-1)
            printf("%d %d", seeds[value_temp].code, seeds[value_temp].score);
        //else
            //printf("%d %d\n",seeds[value_temp].code, seeds[value_temp].score);
    }
    end = clock();
    time_spent_2 = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("\n\nExecution time: %f sec\n\n", time_spent_2);
    printf("Total time: %.3f", time_spent_2+time_spent_1);

    free(seeds);
}


void solution_without_input_nice(){
    clock_t begin, end;
    double time_spent_1;
    int size = 1000000, inferior_range = 0, superior_range = 1, k = 10000, minor_k;
    Seed *seeds = worst_vec(size, inferior_range, superior_range);
    
    minor_k = size-k;

    begin = clock();
    // pegando o menor elemento dos top k e realizando ordenação relativa
    quickSelect(seeds, 0, size-1, minor_k,0);
    // ordenando a partir do menor elemento pra frente
    quickSort(seeds, minor_k, size-1, 1);
    end = clock();

    time_spent_1 = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("\n\nExecution time: %f sec\n\n", time_spent_1);

    free(seeds);
}

void solution_by_input_nice(){
    // k: quantas TOP sementes deverá ser selecionadas
    // max_inputs: 10^7 entradas possíveis para sementes disponibilizada por EDA
    int k, minor_k, value_temp, size, max_inputs = 10000000;
    Seed *seeds = malloc(max_inputs * sizeof(*seeds));

    k = input(); //referente ao npumero de top seeds
    for(size = 0; size < max_inputs; size++){
        value_temp = input(); //Lendo codigo da seed
        if(value_temp != EOF){
            seeds[size].code = value_temp;  
            value_temp = input(); //Lendo nota da seed 
            if(value_temp != EOF)
                seeds[size].score = value_temp; 
            else
                break;
        }  
        else
            break;
    }

    minor_k = size-k;

    // pegando o menor elemento dos top k e realizando ordenação relativa
    quickSelect(seeds, 0, size-1, minor_k,0);
    // ordenando a partir do menor elemento pra frente
    quickSort(seeds, minor_k, size-1, 1);

    for(value_temp = minor_k; value_temp < size; value_temp++){
        if(value_temp == size-1)
            printf("%d %d", seeds[value_temp].code, seeds[value_temp].score);
        else
            printf("%d %d\n",seeds[value_temp].code, seeds[value_temp].score);
    }

    free(seeds);
}

int main(){
    //solution_by_input();
    solution_without_input_nice();
    //solution_by_input_nice();
    return 0;
}
