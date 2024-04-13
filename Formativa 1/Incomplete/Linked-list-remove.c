#include <stdio.h>
#include <stdlib.h>

// Definição da struct celula
typedef struct celula {
    int dado;
    struct celula *prox;
} celula;

// Função para remover o elemento imediatamente seguinte ao ponteiro p
int remove_depois(celula *p) {
    if (p->prox == NULL || p->prox->prox == NULL) {
        // Não é possível remover o próximo elemento
        return 0;
    }
    celula *temp = p->prox;
    p->prox = temp->prox;
    free(temp);
    return 1;
}

// Função para remover a primeira ocorrência de x na lista
void remove_elemento(celula *le, int x) {
    celula *atual = le->prox; //pula nó cabeça
    celula *anterior = le;

    while (atual) {
        if (atual->dado == x) {
            anterior->prox = atual->prox;
            free(atual);
            return; // Remoção concluída
        }
        anterior = atual;
        atual = atual->prox;
    }
}

// Função para remover todas as ocorrências de x na lista
void remove_todos_elementos(celula *le, int x) {
    celula *atual = le->prox;
    celula *anterior = le;

    while (atual) {
        if (atual->dado == x) {
            anterior->prox = atual->prox;
            free(atual);
            atual = anterior->prox; // Continue verificando o próximo nó
        } else {
            anterior = atual;
            atual = atual->prox;
        }
    }
}