#include <stdio.h>
#include <stdlib.h>

/*
* perceba que na estrutura abaixo, optou-se por armazenar o 
* inteiro relativo à tabela ascii do caracter da filas (row).
* Isso facilita o processo de comparação e ordenação.
*/
typedef struct {
    int row;
    int column;
}seat;

/* Leitura de entrada: A leitura da entrada usando scanf("%c%d", &seats[usedSeats].row, &seats[usedSeats].column) pode não funcionar conforme o esperado. O %c lê apenas um caractere, e o %d lê um número inteiro. Se você deseja ler uma string (como ?A1? ou ?B3?), precisará ajustar a lógica de leitura.
*  Considerando que há, no máximo, 500 cadeiras, será utilizado o método 
*  InsertionSort, o qual possui O(n^2) no pior caso. Isso relaciona-se 
*  a um fato meramente didático e de revisão.
*       No caso desse problema, ele cumpre seu papel, mas em casos que neces-
*  sitam de maior eficiência, recomenda-se, por exemplo, arvore binária,
*  o qual possui O(log n).
*       Além disso, nesse problema, um caminho é percorrer, no pior caso,
*  o vetor de cadeiras ocupados desordenados (n, n-1, n-2,..., 2, 1) vezes 
*  a cada cadeira, implicando em O(n³).
*/

void insertionSort(seat *array, int size){
    for (int i = 1; i < size; i++){
        seat key = array[i]; 
        int j = i - 1;
        while (j >= 0 && array[j].row <= key.row){ //sentido: decrescente
            // a ordenação buscada - ex.: [C2,B1,B2,A1,A3]
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
        printf("Erro na alocação de memória.\n");
        exit(1);
    }

    while (scanf("%c%d\n", &seats[usedSeats].row, &seats[usedSeats].column) != EOF && usedSeats < totalSeats)
        seats = (seat*) realloc (seats, (++usedSeats) * sizeof(seat));  // realloc repetidas vezes é ineficiente e considerado como malware para o sistema

    //Ordenar lista de lugares ocupados
    insertionSort(seats, usedSeats);

    return seats;
}

int cineMap(int rows, int columns){
    seat *UsedSeats = SeatAlloc(rows, columns); // O(n + n²) == O(n²)
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
* Fui até o prof mostrar o código, o primeiro fator levantado por ele é a utilização demasiada no while de realloc.
* Esse fato é interpretado pelo compilador como um malware, pois alocação e realocação frequentes podem levar à 
* fragmentação de memória e, por sua vez, afetando negativamente o desempenho do programa. Além disso, realocação de
* memória é muito custoso, haja visto que ele copia todos os dados no vetor anterior para alocar no novo bloco.
* O número de realocações não é um problema em si, mas a frequência e o tamanho das realocações importam. Se você 
* realocar muitas vezes em um loop, o programa pode ficar mais lento. É melhor alocar espaço suficiente desde o 
* início ou minimizar as realocações.
* Além desse fato, não é necessário armazenar em vetor as cadeiras e ordená-las, pois isso implica no acrescimo 
* considerável e desnecessário de tempo de execução, um caminho é ir catalogando linha a linha as cadeiras diretamente. 
*
* Alternativas:
* Alocar um tamanho inicial maior (se possível).
* Realocar apenas quando necessário (por exemplo, como no JAVA).
* Usar estruturas de dados que minimizem a necessidade de realocação (como lista encadeada).
*/