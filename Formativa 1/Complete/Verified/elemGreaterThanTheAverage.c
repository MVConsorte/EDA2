#include <stdio.h>
#include <stdlib.h>

void elemGreaterThanAverage(int N){
    int i = 0;
    long int *seq = (long int*) malloc (N * sizeof(long int)), sum = 0;
    //obter valores da seq
    while(i < N){
        //verificar se eh long inteiro p/incrementar -> anexa valor na seq
        if(scanf("%ld", &seq[i]) == 1) {
            sum += seq[i]; //Var de somatorio dos elementos
            i++;
        } 
    }

    for(long int i = 0, j = 0; i <= N-1; i++){
        // elem > media da sequencia
        if (seq[i] > (sum/N)) {
            if(j == 0) printf("%ld", seq[i]);
            else printf(" %ld", seq[i]);
            j++; //incrementar flag de primeiro elemento
            seq[0] = -1; //flag indicando q há elemento > media
        }
    }
    if(seq[0] != -1) printf("%d",0);
    free(seq); //liberar mem heap alocada
}

int main (){
    long int tamSeq;
    //obter tamanho do vetor (numero de elementos)
    scanf("%ld", &tamSeq);
    elemGreaterThanAverage(tamSeq);
    return 0;
}