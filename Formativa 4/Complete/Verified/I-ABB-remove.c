#include <stdio.h>
#include <stdlib.h>

// Definição da struct no
typedef struct no {
    int chave;
    struct no *esq, *dir;
} no;

// Função para criar um novo nó
no *criarNo(int chave) {
    no *novo = (no *)malloc(sizeof(no));
    novo->chave = chave;
    novo->esq = novo->dir = NULL;
    return novo;
}

// Função para inserir um valor na árvore
no *inserir(no *r, int x) {
    if (r == NULL)
        return criarNo(x);
    if (x < r->chave)
        r->esq = inserir(r->esq, x);
    else if (x > r->chave)
        r->dir = inserir(r->dir, x);
    return r;
}

// Função para encontrar o antecessor
no *antecessor(no *r) {
    while (r->dir != NULL)
        r = r->dir;
    return r;
}

// Função para remover um valor da árvore
no *remover(no *r, int x) {
    if (r == NULL)
        return r;

    if (x < r->chave)
        r->esq = remover(r->esq, x);
    else if (x > r->chave)
        r->dir = remover(r->dir, x);
    else {
        // Nó com apenas um filho ou nenhum filho
        if (r->esq == NULL) {
            no *temp = r->dir;
            free(r);
            return temp;
        } else if (r->dir == NULL) {
            no *temp = r->esq;
            free(r);
            return temp;
        }

        // Nó com dois filhos: encontre o antecessor
        no *temp = antecessor(r->esq);
        r->chave = temp->chave;
        r->esq = remover(r->esq, temp->chave);
    }
    return r;
}