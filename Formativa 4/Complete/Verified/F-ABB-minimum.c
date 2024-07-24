#include <stdio.h>

typedef struct no {
   int chave;
   struct no *esq, *dir;
} no;

no *minimo (no *r);

no *minimo (no *r){
    no *prev = NULL;
    for(no *current = r; current != NULL; current = current->esq)
        prev = current;
    return prev;
}