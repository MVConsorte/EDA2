#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct NoBST {
    char alimento[100];
    struct NoBST *esquerda, *direita;
} NoBST;

typedef struct TabelaHash {
    int colonia_id;
    NoBST *alimentos;
    struct TabelaHash *proximo;
} TabelaHash;

int funcao_hash(int colonia_id) {
    return colonia_id % 1048576;
}

TabelaHash *tabela_hash[1048576];

NoBST* criar(char *comida) {
    NoBST *novo_no = (NoBST *)calloc(sizeof(NoBST));
    strcpy(novo_no->alimento, comida);
    novo_no->esquerda = novo_no->direita = NULL;
    return novo_no;
}

int buscar(NoBST *raiz, char *comida) {
    if (raiz == NULL) return 0;
    int cmp = strcmp(comida, raiz->alimento);
    if (cmp == 0) return 1;
    else if (cmp < 0) return buscar(raiz->esquerda, comida);
    else return buscar(raiz->direita, comida);
}

NoBST* inserir(NoBST *raiz, char *comida) {
    if (raiz == NULL) return criar(comida);
    int cmp = strcmp(comida, raiz->alimento);
    if (cmp < 0) raiz->esquerda = inserir(raiz->esquerda, comida);
    else if (cmp > 0) raiz->direita = inserir(raiz->direita, comida);
    return raiz;
}

TabelaHash* criar_hash(int id, char *comida) {
    TabelaHash *novo_no = (TabelaHash *)calloc(1,sizeof(TabelaHash));
    novo_no->colonia_id = id;
    novo_no->alimentos = criar(comida);
    return novo_no;
}


void inserir_tabela_hash(int id, char *comida) {
    int indice_hash = funcao_hash(id);
    TabelaHash *entrada = tabela_hash[indice_hash];
    if (entrada == NULL) {
        tabela_hash[indice_hash] = criar_hash(id, comida);
    } else {
        TabelaHash *prev = NULL;
        for (entrada = tabela_hash[indice_hash]; entrada != NULL; prev = entrada, entrada = entrada->proximo) {
            if (entrada->colonia_id == id) break;
        }
        if (entrada == NULL) {
            prev->proximo = criar_hash(id, comida);
        } else {
            if (buscar(entrada->alimentos, comida)) {
                printf("%d\n", id);
            } else {
                entrada->alimentos = inserir(entrada->alimentos, comida);
            }
        }
    }
}

int main() {
    char l1[100];
    char comida[100];
    int id;

    while (fgets(l1, sizeof(l1), stdin) != NULL) {
        sscanf(l1, "%d %s", &id, comida);
        inserir_tabela_hash(id, comida);
    }

    return 0;
}
