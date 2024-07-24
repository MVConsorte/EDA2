#include <stdio.h>
#include <stdlib.h>



typedef struct no {
    int vertice;
    struct no* proximo;
} no;

typedef struct grafos {
    no* adj[200001];
    int tam;
} grafos;

grafos* criar_grafos(int tam) {
    grafos* g = (grafos*) malloc(sizeof(grafos));
    g->tam = tam;
    for (int i = 1; i <= tam; i++)
        g->adj[i] = NULL;
    return g;
}

void inserir_grafo(grafos* g, int u, int v) {
    no* novo = (no*) malloc(sizeof(no));
    novo->vertice = v;
    novo->proximo = g->adj[u];
    g->adj[u] = novo;
}

void destroi_grafos(grafos* g) {
    for (int i = 1; i <= g->tam; i++) {
        no* atual = g->adj[i];
        while (atual != NULL) {
            no* temp = atual;
            atual = atual->proximo;
            free(temp);
        }
    }
    free(g);
}

void dfs(grafos* g, int v, int* visitado, int* custo, int* Res) {
    visitado[v] = 1;
    *custo |= v;
    no* adj = g->adj[v];
    while (adj != NULL) {
        if (!visitado[adj->vertice])
            dfs(g, adj->vertice, visitado, custo, Res);
        adj = adj->proximo;
    }
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    grafos* g = criar_grafos(N);

    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        inserir_grafo(g, u, v);
        inserir_grafo(g, v, u);
    }

    int visitado[200001] = {0};
    int resultado = 0;

    for (int i = 1; i <= N; i++) {
        if (!visitado[i]) {
            int custo = 0;
            dfs(g, i, visitado, &custo, &resultado);
            resultado ^= custo;
        }
    }

    printf("%d\n", resultado);

    return 0;
}
