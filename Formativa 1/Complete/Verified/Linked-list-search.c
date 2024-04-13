#include <stdio.h>
#include <stdlib.h>

// Defini��o da estrutura da c�lula
typedef struct celula {
    int dado;
    struct celula *prox;
} celula;

// Fun��o para buscar a primeira ocorr�ncia de um elemento na lista encadeada
celula *busca(celula *le, int x) {
    celula *p = le->prox; // Comece a partir do primeiro elemento (pule o n� cabe�a)
    while (p != NULL) {
        if (p->dado == x) {
            return p; // Encontrou o elemento, retorne o ponteiro para a c�lula
        }
        p = p->prox;
    }
    return NULL; // Elemento n�o encontrado
}

// Fun��o recursiva para buscar um elemento na lista encadeada
celula *busca_rec(celula *le, int x) {
    if (le == NULL) {
        return NULL; // Lista vazia ou final da lista
    }
    if (le->dado == x) {
        return le; // Encontrou o elemento, retorne o ponteiro para a c�lula
    }
    return busca_rec(le->prox, x); // Continue procurando na pr�xima c�lula
}