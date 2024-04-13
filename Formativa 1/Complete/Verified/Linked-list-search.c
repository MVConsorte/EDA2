#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura da célula
typedef struct celula {
    int dado;
    struct celula *prox;
} celula;

// Função para buscar a primeira ocorrência de um elemento na lista encadeada
celula *busca(celula *le, int x) {
    celula *p = le->prox; // Comece a partir do primeiro elemento (pule o nó cabeça)
    while (p != NULL) {
        if (p->dado == x) {
            return p; // Encontrou o elemento, retorne o ponteiro para a célula
        }
        p = p->prox;
    }
    return NULL; // Elemento não encontrado
}

// Função recursiva para buscar um elemento na lista encadeada
celula *busca_rec(celula *le, int x) {
    if (le == NULL) {
        return NULL; // Lista vazia ou final da lista
    }
    if (le->dado == x) {
        return le; // Encontrou o elemento, retorne o ponteiro para a célula
    }
    return busca_rec(le->prox, x); // Continue procurando na próxima célula
}