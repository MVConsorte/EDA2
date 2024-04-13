#include <stdio.h>
#include <stdlib.h>

// Definição da struct celula
typedef struct celula {
    int dado;
    struct celula *prox;
} celula;

// Função iterativa para imprimir a lista encadeada
void imprime(celula *le) {
    celula *atual = le->prox; // Pula o nó cabeça
    while (atual) {
        printf("%d -> ", atual->dado);
        atual = atual->prox;
    }
    printf("NULL\n");
} 

// Função recursiva para imprimir a lista encadeada
void imprime_rec(celula *le) {
    //pula o nó cabeça
    if (le->prox) {
        printf("%d -> ", le->prox->dado);
        imprime_rec(le->prox);
    } else {
        printf("NULL\n");
    }
}
