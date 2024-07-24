#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_X 1000
#define MAX_Y 1000

char mapa[MAX_Y][MAX_X];
bool visitado[MAX_Y][MAX_X];
int dx[] = {1, -1, 0, 0}; 
int dy[] = {0, 0, 1, -1};

typedef struct No {
    int x, y;
    struct No* proximo;
} No;

No* inicio_fila = NULL;
No* fim_fila = NULL;

void enfileirar(int x, int y) {
    No* novoNo = (No*)malloc(sizeof(No));
    novoNo->x = x;
    novoNo->y = y;
    novoNo->proximo = NULL;

    if (fim_fila == NULL) {
        inicio_fila = fim_fila = novoNo;
    } else {
        fim_fila->proximo = novoNo;
        fim_fila = novoNo;
    }
}

void desenfileirar() {
    if (inicio_fila == NULL) return;

    No* temp = inicio_fila;
    inicio_fila = inicio_fila->proximo;

    if (inicio_fila == NULL) {
        fim_fila = NULL;
    }

    free(temp);
}

bool fila_vazia() {
    return inicio_fila == NULL;
}

typedef struct Listadj {
    int vertice;
    struct Listadj* proximo;
} Listadj;

typedef struct Grafo {
    Listadj** adjacencia;
    int tamanho;
} Grafo;

Grafo* criar_grafo(int tamanho) {
    Grafo* g = malloc(sizeof(Grafo));
    g->tamanho = tamanho;
    g->adjacencia = calloc(tamanho, sizeof(Listadj*));
    return g;
}

void inserir_aresta(Grafo* g, int u, int v) {
    Listadj* novoNo = malloc(sizeof(Listadj));
    novoNo->vertice = v;
    novoNo->proximo = g->adjacencia[u];
    g->adjacencia[u] = novoNo;
}

void destruir_grafo(Grafo* g) {
    for (int i = 0; i < g->tamanho; i++) {
        Listadj* atual = g->adjacencia[i];
        while (atual) {
            Listadj* temp = atual;
            atual = atual->proximo;
            free(temp);
        }
    }
    free(g->adjacencia);
    free(g);
}

int largura, altura;

bool dentro_do_mapa(int nx, int ny) {
    return nx >= 0 && ny >= 0 && nx < largura && ny < altura;
}

char bfs() {
    enfileirar(0, 0);
    visitado[0][0] = true;

    while (!fila_vazia()) {
        int cx = inicio_fila->x;
        int cy = inicio_fila->y;
        desenfileirar();

        char atual = mapa[cy][cx];

        if (atual == '*') {
            return '*';
        }

        if (atual == '.' || atual == '>' || atual == '<' || atual == 'v' || atual == '^') {
            int direcao;
            if (atual == '>') direcao = 0;
            else if (atual == '<') direcao = 1;
            else if (atual == 'v') direcao = 2;
            else if (atual == '^') direcao = 3;

            int nx = cx + dx[direcao];
            int ny = cy + dy[direcao];

            if (dentro_do_mapa(nx, ny) && !visitado[ny][nx]) {
                visitado[ny][nx] = true;
                enfileirar(nx, ny);
            }
        }
    }

    return '!';
}

int main() {
    scanf("%d", &largura);
    scanf("%d", &altura);

    for (int i = 0; i < altura; ++i) {
        scanf("%s", mapa[i]);
    }

    char resultado = bfs();
    printf("%c\n", resultado);

    return 0;
}
