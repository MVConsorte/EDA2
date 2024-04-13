#include <stdio.h>
#include <stdlib.h>

/*
* perceba que na estrutura abaixo, optou-se por armazenar o 
* inteiro relativo � tabela ascii do caracter da filas (row).
* Isso facilita o processo de compara��o e ordena��o.
*/
typedef struct {
    int row;
    int column;
}seat;

/* Leitura de entrada: A leitura da entrada usando scanf("%c%d", &seats[usedSeats].row, &seats[usedSeats].column) pode n�o funcionar conforme o esperado. O %c l� apenas um caractere, e o %d l� um n�mero inteiro. Se voc� deseja ler uma string (como ?A1? ou ?B3?), precisar� ajustar a l�gica de leitura.
*  Considerando que h�, no m�ximo, 500 cadeiras, ser� utilizado o m�todo 
*  InsertionSort, o qual possui O(n^2) no pior caso. Isso relaciona-se 
*  a um fato meramente did�tico e de revis�o.
*       No caso desse problema, ele cumpre seu papel, mas em casos que neces-
*  sitam de maior efici�ncia, recomenda-se, por exemplo, arvore bin�ria,
*  o qual possui O(log n).
*       Al�m disso, nesse problema, um caminho � percorrer, no pior caso,
*  o vetor de cadeiras ocupados desordenados (n, n-1, n-2,..., 2, 1) vezes 
*  a cada cadeira, implicando em O(n�).
*/

void insertionSort(seat *array, int size){
    for (int i = 1; i < size; i++){
        seat key = array[i]; 
        int j = i - 1;
        while (j >= 0 && array[j].row <= key.row){ //sentido: decrescente
            // a ordena��o buscada - ex.: [C2,B1,B2,A1,A3]
            if (array[j].row != key.row || array[j].column > key.column){
                array[j+1] = array[j];
                j--;
            }
        }
        array[j+1] = key;
    }
}

seat *SeatAlloc(int rows, int columns){
    int usedSeats = 0, totalSeats = rows*columns; //lugares ocupados, max lugares usados
    seat *seats = (seat*) malloc ((usedSeats + 1) * sizeof(seat));  //definindo um tamanho inicial
    
    if(seats == NULL){
        printf("Erro na aloca��o de mem�ria.\n");
        exit(1);
    }

    while (scanf("%c%d\n", &seats[usedSeats].row, &seats[usedSeats].column) != EOF && usedSeats < totalSeats)
        seats = (seat*) realloc (seats, (++usedSeats) * sizeof(seat));  // realloc repetidas vezes � ineficiente e considerado como malware para o sistema

    //Ordenar lista de lugares ocupados
    insertionSort(seats, usedSeats);

    return seats;
}

int cineMap(int rows, int columns){
    seat *UsedSeats = SeatAlloc(rows, columns); // O(n + n�) == O(n�)
    if(UsedSeats == NULL) return 1;

    int rowA = 65; // definindo iterador da letra A (65) (na tabela ascii)

    for (int i = 0; i < rows; i++){
        for(int j = 0; j < columns; j++){
            if(i == 0){
                if(j == 0) printf("  ");
                else if (j == 1) printf("%.2d", i+1);
                else printf(" %.2d", i+1);
            } 
            else {
                if(j == 0) printf("%c", rowA++);
                else {
                    if(UsedSeats[j].column == j) printf(" %s", "XX");
                    else printf(" %s","--");
                }
            }
        }
    }
    free(UsedSeats);
    return 0;
}

int main(){
    int rows, nums;
    scanf("%d %d", &rows, &nums);
    cineMap(rows, nums);
    return 0;
}


/*
* Fui at� o prof mostrar o c�digo, o primeiro fator levantado por ele � a utiliza��o demasiada no while de realloc.
* Esse fato � interpretado pelo compilador como um malware, pois aloca��o e realoca��o frequentes podem levar � 
* fragmenta��o de mem�ria e, por sua vez, afetando negativamente o desempenho do programa. Al�m disso, realoca��o de
* mem�ria � muito custoso, haja visto que ele copia todos os dados no vetor anterior para alocar no novo bloco.
* O n�mero de realoca��es n�o � um problema em si, mas a frequ�ncia e o tamanho das realoca��es importam. Se voc� 
* realocar muitas vezes em um loop, o programa pode ficar mais lento. � melhor alocar espa�o suficiente desde o 
* in�cio ou minimizar as realoca��es.
* Al�m desse fato, n�o � necess�rio armazenar em vetor as cadeiras e orden�-las, pois isso implica no acrescimo 
* consider�vel e desnecess�rio de tempo de execu��o, um caminho � ir catalogando linha a linha as cadeiras diretamente. 
*
* Alternativas:
* Alocar um tamanho inicial maior (se poss�vel).
* Realocar apenas quando necess�rio (por exemplo, como no JAVA).
* Usar estruturas de dados que minimizem a necessidade de realoca��o (como lista encadeada).
*/