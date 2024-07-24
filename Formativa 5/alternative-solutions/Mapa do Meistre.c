#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

char mapa[100][100];       // Matriz para armazenar o mapa
bool visitado[100][100];   // Matriz booleana para marcar os lugares visitadas
int largura, altura;       // Dimensões do mapa

// Vetores de direção para movimentos: direita, esquerda, baixo e cima
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

// Estrutura para representar um ponto no mapa
typedef struct No {
    int x, y;  // Coordenadas do ponto
} No;


No fila[100 * 100];
int inicio_fila = 0;
int fim_fila = 0;


void enfileirar(int x, int y) {
    fila[fim_fila].x = x;
    fila[fim_fila].y = y;
    fim_fila = (fim_fila + 1) % (100 * 100);
}


void desenfileirar() {
    inicio_fila = (inicio_fila + 1) % (100 * 100);
}


bool fila_vazia() {
    return inicio_fila == fim_fila;
}

// Função para verificar se um ponto (nx, ny) está dentro dos limites do mapa
bool dentro_do_mapa(int nx, int ny) {
    return nx >= 0 && ny >= 0 && nx < largura && ny < altura;
}


char bfs() {
    enfileirar(0, 0);  // Adiciona o ponto inicial (0, 0) à fila
    visitado[0][0] = true;  // Marca o ponto inicial como visitado

    // Loop para processar a fila enquanto ela não estiver vazia
    while (!fila_vazia()) {
        int cx = fila[inicio_fila].x;  // Pega a coordenada x do ponto no início da fila
        int cy = fila[inicio_fila].y;  // Pega a coordenada y do ponto no início da fila
        desenfileirar();  // Remove o ponto do início da fila

        char atual = mapa[cy][cx];  // Obtém o caractere no mapa na posição atual

        // Verifica se o ponto atual é a célula alvo
        if (atual == '*') {
            return '*';  // Se encontrar a célula alvo, retorna '*'
        }

        // Verifica se o ponto atual é um caminho ou uma direção
        if (atual == '.' || atual == '>' || atual == '<' || atual == 'v' || atual == '^') {
            int direcao;  // Variável para armazenar a direção do movimento

            // Determina a direção com base no caractere atual
            if (atual == '>') direcao = 0;  // Direita
            else if (atual == '<') direcao = 1;  // Esquerda
            else if (atual == 'v') direcao = 2;  // Baixo
            else if (atual == '^') direcao = 3;  // Cima

            // Calcula as novas coordenadas baseadas na direção
            int nx = cx + dx[direcao];
            int ny = cy + dy[direcao];

            // Verifica se a nova posição está dentro dos limites do mapa e não foi visitada
            if (dentro_do_mapa(nx, ny) && !visitado[ny][nx]) {
                visitado[ny][nx] = true;  // Marca a nova posição como visitada
                enfileirar(nx, ny);  // Adiciona a nova posição à fila
            }
        }
    }

    return '!'; 
}

int main() {
    char input_buffer[BUFSIZ];
    setvbuf(stdin, input_buffer, _IOFBF, BUFSIZ);
    setvbuf(stdout, NULL, _IOFBF, 0);

    scanf("%d %d\n", &largura, &altura);

    for (int i = 0; i < altura; ++i) {
        fgets(mapa[i], sizeof(mapa[i]), stdin);
    }

    char resultado = bfs();
    printf("%c\n", resultado);

    return 0;  
}
