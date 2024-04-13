#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura da célula
typedef struct celula {
    int dado;
    struct celula *prox;
} celula;

void mescla_listas (celula *l1, celula *l2, celula *l3);

// Função para mesclar duas listas encadeadas ordenadas
void mescla_listas(celula *l1, celula *l2, celula *l3) {
    celula *p1 = l1->prox; // Pule o nó cabeça de l1
    celula *p2 = l2->prox; // Pule o nó cabeça de l2
    celula *p3 = l3;       // Comece com o nó cabeça de l3

    while (p1 != NULL && p2 != NULL) {
        if (p1->dado <= p2->dado) {
            p3->prox = p1;
            p1 = p1->prox;
        } else {
            p3->prox = p2;
            p2 = p2->prox;
        }
        p3 = p3->prox;
    }

    // Se ainda houver elementos em l1 ou l2, anexe-os a l3
    if (p1 != NULL) {
        p3->prox = p1;
    } else {
        p3->prox = p2;
    }
}

