#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct no {
    int vertice;
    struct no* proximo;
} no;

typedef struct grafos {
    no** adjencia;
    int tam;
} grafos;

grafos* criar_grafos(int tam) {
    grafos* g = malloc(sizeof(grafos));
    g->tam = tam;
    g->adjencia = calloc(tam, sizeof(no*));
    return g;
}

void inserir_grafos(grafos* g, int u, int v) {
    no* novo = malloc(sizeof(no));
    novo->vertice = v;
    novo->proximo = g->adjencia[u];
    g->adjencia[u] = novo;
}

void destroi_grafos(grafos* g) {
    for (int i = 0; i < g->tam; i++) {
        no* atual = g->adjencia[i];
        while (atual) {
            no* temp = atual;
            atual = atual->proximo;
            free(temp);
        }
    }
    free(g->adjencia);
    free(g);
}

void bfs(grafos* g, int* tipo_maca, int n) {
    int* green_count = calloc(n, sizeof(int));
    int* red_count = calloc(n, sizeof(int));
    bool* visitado = calloc(n, sizeof(bool));
    int* queue = malloc(n * sizeof(int));
    int front = 0, rear = 0;

    queue[rear++] = 0; 
    visitado[0] = true;

    int level = 0;
    while (front < rear) {
        int level_size = rear - front;
        int green_this_level = 0;
        int red_this_level = 0;
        for (int i = 0; i < level_size; i++) {
            int v = queue[front++];
            if (tipo_maca[v] == 1) green_this_level++;
            if (tipo_maca[v] == 2) red_this_level++;
            for (no* adj = g->adjencia[v]; adj != NULL; adj = adj->proximo) {
                if (!visitado[adj->vertice]) {
                    queue[rear++] = adj->vertice;
                    visitado[adj->vertice] = true;
                }
            }
        }
        if (green_this_level > 0 || red_this_level > 0) {
            green_count[level] = green_this_level;
            red_count[level] = red_this_level;
            level++;
        }
    }

    for (int i = 0; i < level; i++) {
        printf("%d %d\n", green_count[i], red_count[i]);
    }


}

int main() {
    int N;
    scanf("%d", &N);

    grafos* g = criar_grafos(N);
    int* tipo_maca = malloc(N * sizeof(int));
    int L, R;

    for (int i = 0; i < N; i++) {
        scanf("%d %d %d", &tipo_maca[i], &L, &R);
        if (L != 0) inserir_grafos(g, i, L - 1);
        if (R != 0) inserir_grafos(g, i, R - 1);
    }

    bfs(g, tipo_maca, N);

    
    return 0;
}
