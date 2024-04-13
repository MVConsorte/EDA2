#include <stdio.h>
#include <stdlib.h>

// Defini��o da struct celula
typedef struct celula {
    int dado;
    struct celula *prox;
} celula;

// Fun��o para remover o elemento imediatamente seguinte ao ponteiro p
int remove_depois(celula *p) {
    if (p->prox == NULL || p->prox->prox == NULL) {
        // N�o � poss�vel remover o pr�ximo elemento
        return 0;
    }
    celula *temp = p->prox;
    p->prox = temp->prox;
    free(temp);
    return 1;
}

// Fun��o para remover a primeira ocorr�ncia de x na lista
void remove_elemento(celula *le, int x) {
    celula *atual = le->prox; //pula n� cabe�a
    celula *anterior = le;

    while (atual) {
        if (atual->dado == x) {
            anterior->prox = atual->prox;
            free(atual);
            return; // Remo��o conclu�da
        }
        anterior = atual;
        atual = atual->prox;
    }
}

// Fun��o para remover todas as ocorr�ncias de x na lista
void remove_todos_elementos(celula *le, int x) {
    celula *atual = le->prox;
    celula *anterior = le;

    while (atual) {
        if (atual->dado == x) {
            anterior->prox = atual->prox;
            free(atual);
            atual = anterior->prox; // Continue verificando o pr�ximo n�
        } else {
            anterior = atual;
            atual = atual->prox;
        }
    }
}