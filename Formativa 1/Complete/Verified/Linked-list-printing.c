#include <stdio.h>
#include <stdlib.h>

// Defini��o da struct celula
typedef struct celula {
    int dado;
    struct celula *prox;
} celula;

// Fun��o iterativa para imprimir a lista encadeada
void imprime(celula *le) {
    celula *atual = le->prox; // Pula o n� cabe�a
    while (atual) {
        printf("%d -> ", atual->dado);
        atual = atual->prox;
    }
    printf("NULL\n");
} 

// Fun��o recursiva para imprimir a lista encadeada
void imprime_rec(celula *le) {
    //pula o n� cabe�a
    if (le->prox) {
        printf("%d -> ", le->prox->dado);
        imprime_rec(le->prox);
    } else {
        printf("NULL\n");
    }
}
