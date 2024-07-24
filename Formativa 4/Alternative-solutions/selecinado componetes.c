#include <stdio.h>
#include <stdlib.h>

void troca(int *x, int *y) {
    int t = *x;
    *x = *y;
    *y = t;
}

void down(int *heap, int start, int end, int min_heap) {
    int raiz = start;
    while ((raiz << 1) + 1 <= end) {
        int filho = (raiz << 1) + 1;
        int trocar = raiz;
        if ((min_heap && heap[trocar] > heap[filho]) || (!min_heap && heap[trocar] < heap[filho]))
            trocar = filho;
        if (filho + 1 <= end && ((min_heap && heap[trocar] > heap[filho + 1]) || (!min_heap && heap[trocar] < heap[filho + 1])))
            trocar = filho + 1;
        if (trocar == raiz)
            break;
        troca(&heap[raiz], &heap[trocar]);
        raiz = trocar;
    }
}

void inserir(int *heap, int *tam, int valor, int min_heap) {
    int j = (*tam)++;
    heap[j] = valor;
    while (j != 0) {
        int pai = (j - 1) >> 1;
        if ((min_heap && heap[j] >= heap[pai]) || (!min_heap && heap[j] <= heap[pai]))
            break;
        troca(&heap[j], &heap[pai]);
        j = pai;
    }
}

int remover(int *heap, int *tam, int min_heap) {
    int raiz = heap[0];
    heap[0] = heap[--(*tam)];
    down(heap, 0, *tam - 1, min_heap);
    return raiz;
}

int main() {
    int N, X;
    scanf("%d %d", &N, &X);

    int minerais[N];
    int tam_min_heap = 0, tam_max_heap = 0;
    int combinacoes[N]; 
    int count_combinacoes = 0; 

    int min_heap[N]; 
    int max_heap[N]; 

    for (int i = 0; i < N; i++) {
        scanf("%d", &minerais[i]);
        inserir(min_heap, &tam_min_heap, minerais[i], 1);
    }

    while (tam_min_heap > 0) {
        int menor = remover(min_heap, &tam_min_heap, 1);
        if (tam_max_heap > 0) {
            int maior = remover(max_heap, &tam_max_heap, 0);
            int diferenca = abs(menor - maior);
            if (diferenca > 0 && diferenca <= X) {
                combinacoes[count_combinacoes++] = menor + maior;
            } else {
                inserir(max_heap, &tam_max_heap, maior, 0);
                inserir(max_heap, &tam_max_heap, menor, 0);
            }
        } else {
            inserir(max_heap, &tam_max_heap, menor, 0);
        }
    }

    printf("%d\n", count_combinacoes);
    for (int i = 0; i < count_combinacoes; i++) {
        printf("%d ", combinacoes[i]);
    }
    printf("\n");

    return 0;
}
