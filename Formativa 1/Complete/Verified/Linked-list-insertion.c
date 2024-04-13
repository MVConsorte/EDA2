#include <stdio.h>
#include <stdlib.h>

// Defini��o da struct celula
typedef struct celula {
    int dado;
    struct celula *prox;
} celula;

// Fun��o para inserir um elemento no in�cio da lista
void insere_inicio (celula *le, int x){
    celula *new_node = (celula *) malloc(sizeof(celula));
    //le->dado++; //incrementar qtd de elementos da lista
    new_node->dado = x;
    new_node->prox = le->prox; //o prox celula � a raiz anterior
    le->prox = new_node; //raiz anterior agr � o novo n�
    //printf("%d",le->dado);
}

// Fun��o para inserir um elemento antes da primeira ocorr�ncia de um valor y
void insere_antes(celula *le, int x, int y) {
    celula *atual = le->prox;
    celula *anterior = le;

    while (atual) {
        if (atual->dado == y) {
            celula *novo = (celula *)malloc(sizeof(celula));
            novo->dado = x;
            novo->prox = atual;
            anterior->prox = novo;
            return; // Inser��o conclu�da
        }
        anterior = atual;
        atual = atual->prox;
    }

    // Se n�o encontrou o valor y, insere ao final
    celula *novo = (celula *)malloc(sizeof(celula));
    novo->dado = x;
    novo->prox = NULL;
    anterior->prox = novo;
}