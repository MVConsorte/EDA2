#include <stdio.h>
#include <stdlib.h>

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

void listened(/*int length_area, int width_area,*/Position *stalked, Position mic, int range_mic){ 
    int steps, direction, recorded_time = 0; //recorded_time(minutos)
    scanf("%d", &steps);

    // iterações (em minutos)
    while(steps > 0){
        scanf("%d", &direction);
        walk(direction, stalked);
        // verificar se os escutados estão no range da escuta
        if(abs(stalked->x - mic.x) <= range_mic && abs(stalked->y - mic.y) <= range_mic)
            recorded_time++;
        steps--;
    }

    // imprimindo numero de minutos escutados
    printf("%d", recorded_time);
}

//obs.: percebi q resolvi o problema sem precisar usar as dimensões do parque

int main(){
    int park_lines, park_columns;
    Position mic, mens = {0,0};  //por padrão inicia em (0,0)
    scanf("%d %d", &park_lines, &park_columns);
    scanf("%d %d", &mic.x, &mic.y);
    listened(/*park_columns, park_lines,*/&mens, mic, 1);
    return 0;
}