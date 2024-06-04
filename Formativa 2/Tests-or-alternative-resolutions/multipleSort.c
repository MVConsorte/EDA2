#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int i; // linha
    int j; // coluna
    double value;
} Problem;

//// MergeSort algorithm  (Est�vel & O(nlogn)); Contrapartida: Necessita de vetor auxiliar

// modificando para atender o requisito de value double e vetor 'Problem'
void intercala(Problem *v, int e, int m, int d){
    Problem *w = malloc((d-e+1) * sizeof(*w));
    int i = e, j = m+1, k = 0;
    while (i<= m && j <= d){
        /* 
        // Para ordem crescente de coluna e, dopois, em ordem crescente de linha retire
        if(v[i].value == v[j].value){
            if(v[i].i > v[j].i)  // padr�o: j
                w[k++] = v[j++];
            else if(v[i].i == v[j].i){ //padr�o: j
                if(v[i].j > v[j].j)  //padr�o: i
                    w[k++] = v[j++];
                else  
                    w[k++] = v[i++];     
            }else
                w[k++] = v[i++];
        }
        
        else*/ 
        if (v[i].value >= v[j].value) // para ordem crescente de coluna e, dopois, em ordem crescente de linha, troque '>=' por '>'
            w[k++] = v[i++];  //(padrao: i++)
        else 
            w[k++] = v[j++]; // (padrao: j++) 
        // fazendo a invers�o de j -> i & i -> j, implica que a coluna tem prefer�ncia sobre a linha
    }
    while (i <= m) w[k++] = v[i++];
    while (j <= d) w[k++] = v[j++];
    for (k=0, i=e;i <= d; i++, k++) v[i] = w[k];
    free(w);
}

// adaptando o mergeSort e intercala para o problema, vetor de 'Problem'
void mergeSort(Problem *v, int e, int d){
    int m = (d + e)/2;
    if(e < d){
        mergeSort(v, e, m);
        mergeSort(v, m+1, d);
        intercala(v, e, m, d);
    }
}

double input(){
    double value;
    if(scanf("%lf", &value) == 1)
        return value;
    
    return -1;
}

// ----------------------- resolu��o --------------------- //
void multipleSort(int T){
    int k, i, j, M, N, qtd_elem, pos_elem;
    Problem *v;
    char **resultados; // Vetor de strings para armazenar os resultados

    M = input();
    N = input();
    qtd_elem = (M * N);
    resultados = malloc(T * sizeof(char*)); // Aloca espa�o para T resultados

    for(k = 0; k < T; k++){
        v = malloc(qtd_elem * sizeof(*v));
        resultados[k] = malloc((qtd_elem * 5) * sizeof(char)); // Aloca espa�o para a string de sa�da de cada teste

        for(i = 0; i < M; i++){
            for(j = 0; j < N; j++) {
                pos_elem = (i*N)+j;
                v[pos_elem].i = i+1;
                v[pos_elem].j = j+1;
                v[pos_elem].value = input(); //cada membro(i) tem N problemas(j), totalizando (i x N) + j input's.
            }
        }
        
        mergeSort(v, 0, qtd_elem-1); //em ordem decrescente
        
        int offset = 0; // Vari�vel para controlar a posi��o atual na string de sa�da
        for(i = 0; i < qtd_elem; i++) {
            //if(v[i].value == v[i+1].value) //===============***************************===================
                //if(v[i].j < v[i+1].j)
                    offset += sprintf(resultados[k] + offset, "%d,%d ", v[i].i, v[i].j); // Armazena o resultado formatado na string
        }
        free(v);
    }

    // Imprime todos os resultados ap�s a ordena��o
    for(k = 0; k < T; k++){
        printf("%s\n", resultados[k]);
        free(resultados[k]); // Libera a mem�ria da string de sa�da
    }
    free(resultados); // Libera o vetor de strings
}


// ------------------------------------------------------- //

int main(){
    // T: o total de casos de teste
    int T = input();
    multipleSort(T);
    return 0;
}