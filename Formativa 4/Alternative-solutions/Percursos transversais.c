#include <stdio.h>
#include <string.h>

void construirPosOrdem(char *preOrdem, char *emOrdem, int comprimento, char *posOrdem, int *indice) {
    if (comprimento <= 0) {
        return;
    }
    char raiz = preOrdem[0];
    int indiceRaiz = 0;
    for (indiceRaiz = 0; emOrdem[indiceRaiz] != raiz; indiceRaiz++);

    construirPosOrdem(preOrdem + 1, emOrdem, indiceRaiz, posOrdem, indice);
    construirPosOrdem(preOrdem + indiceRaiz + 1, emOrdem + indiceRaiz + 1, comprimento - indiceRaiz - 1, posOrdem, indice);
    posOrdem[*indice] = raiz;
    (*indice)++;
}

int main() {
    int C;
    scanf("%d", &C);

    for (int i = 0; i < C; i++) {
        int N;
        char preOrdem[53], emOrdem[53];
        scanf("%d %s %s", &N, preOrdem, emOrdem);

        char posOrdem[53];
        int indice = 0;
        construirPosOrdem(preOrdem, emOrdem, N, posOrdem, &indice);
        posOrdem[N] = '\0'; 
        printf("%s\n", posOrdem);
    }

    return 0;
}
