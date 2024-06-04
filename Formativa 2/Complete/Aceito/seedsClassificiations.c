#include <stdio.h>
#include <stdlib.h>
//#include <time.h>

typedef struct{
    int code;
    int score;
} Seed;


// ------------ QuickSelect/Sort algorithm for Seed -------------------- //
void troca(Seed *a, Seed *b);
int particiona(Seed *vec, int e, int d,char key);
void cmp_exch(Seed *elem_a, Seed *elem_b);
void median_of_three(Seed *vec, int e, int d);
void quickSelect(Seed *vec, int e, int d, int k, char key); 
void quickSort(Seed *vec, int e, int d, char key);

// ------ Function resolution/input ----- //
int input();
void solution_seeds_classification();


int main(){
    solution_seeds_classification();
    return 0;
}

// --------------------------------------------------------------------- //
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

// ------------------ function view ------------------------------- //

int input(){
    int value, exit = scanf("%d", &value);
    if(exit == 1 || exit != EOF)
        return value;
    else
        return exit;
}

void solution_seeds_classification(){
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