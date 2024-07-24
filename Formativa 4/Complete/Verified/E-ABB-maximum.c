#include <stdio.h>
#include <stdlib.h>

typedef struct no {
   int chave;
   struct no *esq, *dir;
} no;

no *maximo (no *r);

no *maximo (no *r){
    no *current = r, *prev = NULL;
    while(current != NULL){
        prev = current;
        current = current->dir;
    }
    return prev;
}