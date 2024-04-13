#include <stdio.h>
#include <stdlib.h>

#define FIRST_ROW 65

int cinema(int rows, int nums);

int main(){
    int rows, nums;
    // obter numero de fileiras e numeração na sala de cinema
    scanf("%d %d", &rows, &nums);
    // limpa buffer
    fflush(stdin);

    return cinema(rows, nums);
}

/////// functions ////////

int cinema(int rows, int nums){
    //definindo array das fileiras/numeração do cinema
    int totalSeats = rows*nums;
    char cineMap[totalSeats][3]; // 3 = 2 caracteres "-"+"-" e 1 caracter nulo "\0"

    //preenchendo o cineMap com "--" + "\0" (fim de string)
    for (int i = 0; i < totalSeats; i++){
        cineMap[i][0] = '-';
        cineMap[i][1] = '-';
        cineMap[i][2] = '\0';
    }
    
    // laço para obter cada uma das cadeiras ocupadas e marcar no cineMap
    char allocRow;
    int allocNum;
    while(scanf("%c%d", &allocRow, &allocNum) != EOF){
        // calcula o índice, lebrando que allocRow é o valor decimal da letra => subtrair por FIRST_ROW
        if(allocNum > 0 && allocNum <= nums && allocRow >= FIRST_ROW && (allocRow - FIRST_ROW) < rows){
            int index = (allocRow - FIRST_ROW) * nums + (allocNum - 1);
            if(cineMap[index][0] != 'X'){
                cineMap[index][0] = 'X'; 
                cineMap[index][1] = 'X';
            } else {
                //printf("Occupied\n");
            }
            fflush(stdin); //limpar buffer
            
        } else {
            //printf("Invalid declaration. Please enter a valid row-seat pair.\n");
            fflush(stdin); //limpar buffer
        } 
    }

    // laço para printar sala de cinema
    // p/ imprimir indicadores, o deslocamento das fileiras e numeros será 1
    for(int row = rows; row >= 0; row--){
        for(int num = -1; num < nums; num++){
            if(num == -1 && row == rows) printf(" ");
            else if(num == -1) printf("%c", FIRST_ROW + row); //formatando para gerar as letras das fileiras
            else if(row == rows) printf(" %.2d", num+1); //adiciona 0 a esquerda para duas casas && ++num == (1..*)
            else printf(" %s", cineMap[row * nums + num]);  //fazendo a busca de acordo com o deslocamento 
        }
        printf("\n");
    }
}