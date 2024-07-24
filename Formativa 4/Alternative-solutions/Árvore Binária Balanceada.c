#include <stdio.h>
#include <stdlib.h>

#define MAX_N 5001

typedef struct No {
    int filhos[MAX_N];
    int quant_filho;
} No;

No arvore[MAX_N];
int E_balanceada = 1;

int calcular_altura(int no) {
    if (arvore[no].quant_filho == 0) {
        return 1; 
    }

    int altura_maxima = 0;
    int altura_minima = MAX_N;

    int i = 0;
    while (i < arvore[no].quant_filho) {
        int filho = arvore[no].filhos[i];
        int altura = calcular_altura(filho);

        if (altura > altura_maxima) {
            altura_maxima = altura;
        }
        if (altura < altura_minima) {
            altura_minima = altura;
        }
        i++;
    }

    if (altura_maxima - altura_minima > 1) {
        E_balanceada = 0;
    }

    return altura_maxima + 1;
}

int main() {
    int N;
    scanf("%d", &N);

    int i = 1;
    while (i <= N) {
        arvore[i].quant_filho = 0;
        i++;
    }

    i = 2;
    while (i <= N) {
        int pai;
        scanf("%d", &pai);
        arvore[pai].filhos[arvore[pai].quant_filho++] = i;
        i++;
    }

    calcular_altura(1);

    if (E_balanceada) {
        printf("Sim\n");
    } else {
        printf("Nao\n");
    }

    return 0;
}
