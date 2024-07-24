#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct No {
    int vertice;
    struct No* proximo;
} No;

typedef struct {
    No* adjacencia[2000];
    bool visitado[2000];
} Grafo;

Grafo* criar_grafo(int tam) {
    Grafo* g = malloc(sizeof(Grafo));
    int i = 0;
    while (i < tam) {
        g->adjacencia[i] = NULL;
        g->visitado[i] = false;
        i++;
    }
    return g;
}

void inserir_aresta(Grafo* g, int u, int v) {
    No* novo_uv = malloc(sizeof(No));
    novo_uv->vertice = v;
    novo_uv->proximo = g->adjacencia[u];
    g->adjacencia[u] = novo_uv;
}

void liberar_grafo(Grafo* g, int tam) {
    int i = 0;
    while (i < tam) {
        No* atual = g->adjacencia[i];
        while (atual) {
            No* temp = atual;
            atual = atual->proximo;
            free(temp);
        }
        i++;
    }
    free(g);
}

void bfs_simples(Grafo* g, int local) {
    No* vizinho = g->adjacencia[local];
    while (vizinho) {
        g->visitado[vizinho->vertice] = true;
        vizinho = vizinho->proximo;
    }
}

int main() {
    int N, M, J;
    scanf("%d %d %d", &N, &M, &J);

    Grafo* g = criar_grafo(N);

    int i = 0;
    while (i < N) {
        int A;
        scanf("%d", &A);
        int j = 0;
        while (j < A) {
            int vizinho;
            scanf("%d", &vizinho);
            inserir_aresta(g, i, vizinho);
            j++;
        }
        i++;
    }

    i = 0;
    while (i < M) {
        int local;
        scanf("%d", &local);
        g->visitado[local] = true;
        bfs_simples(g, local);
        i++;
    }

    i = 0;
    while (i < J) {
        int consulta;
        scanf("%d", &consulta);
        if (g->visitado[consulta]) {
            printf("Eu vou estar la\n");
        } else {
            printf("Nao vou estar la\n");
        }
        i++;
    }

    return 0;
}
