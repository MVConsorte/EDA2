#include <stdio.h>
#include <stdlib.h>

/*
    O que deve retornar a saída: 
     - Caso os professores tenham se encontrado: as coordenadas do encontro e o passo em 
     que ocorreu.
     - Caso o(s) professor(es) tenha(m) saído do CP (área do campus): as coordenadas em que saíram e o 
     passo em que ocorreu. Se ambos professores saíram no mesmo passo imprima apenas 
     a informação sobre o professor PA.
     - Caso nenhuma das anteriores ocorra, imprimir: ?Nao se encontraram?.
        
    [N] = norte (1); [S] = sul (2); [L] = leste(3); [O] = oeste(4)
        X   Y
    ++  N   L
    --  S   O

    [m] = largura CP; [n] = comprimento CP
    Prof    x   y
    PA      1   1
    PB      n   m
*/

typedef struct {
    int x;
    int y;
} Position;

int walk(int direction, Position *person){
    switch (direction){
        case 1:
            person->y++;
            break;
        case 2:
            person->y--;
            break;
        case 3:
            person->x++;
            break;
        case 4:
            person->x--;
            break;
        default:
            return 1;
            break;
    }
    return 0;
}

int OutBounds(Position person, int lenght, int width){
    if(person.x < 1 || person.y < 1 || person.x > lenght || person.y > width)
        return 1;
    else 
        return 0;
}

int Encounter(int lenght, int width, int steps){
    // definindo posições iniciais dos profs
    Position PA = {1,1}, PB = {lenght,width};
    int step = 0, PA_direction, PB_direction;

    while(steps > 0){
        scanf("%d %d", &PA_direction, &PB_direction);
        // atualiza posição
        walk(PA_direction, &PA);
        walk(PB_direction, &PB);
        steps--; step++;
        // indentificar se alguem saiu do CP
        if(OutBounds(PA, lenght, width) || (OutBounds(PA, lenght, width) && OutBounds(PB, lenght, width))){
            printf("PA saiu na posicao (%d,%d) no passo %d", PA.x, PA.y, step);
            return 1;
        } else if(OutBounds(PB, lenght, width)){
            printf("PB saiu na posicao (%d,%d) no passo %d", PB.x, PB.y, step);
            return 1;
        }
    }
    // verifica se ocorreu encontro ou não houve encontro
    if(PA.x == PB.x && PA.y == PB.y)
        printf("Encontraram-se na posicao (%d,%d) no passo %d", PA.x, PA.y, step);
    else
        printf("Nao se encontraram");
    return 0;
}

int main(){
    int comprimento,largura, passos;
    scanf("%d %d", &comprimento, &largura);
    scanf("%d", &passos);
    Encounter(comprimento, largura, passos);
    return 0;
}