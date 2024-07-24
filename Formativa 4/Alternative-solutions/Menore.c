#include <stdio.h>
#include <stdlib.h>

#define NUlo -1

typedef int Item;

void troca(Item *a, Item *b) {
    Item t = *a;
    *a = *b;
    *b = t;
}

typedef struct {
    Item *heap;
    int tamanho, capacidade;
} FilaPrioridade;

FilaPrioridade FP_inicia(int capacidade) {
    FilaPrioridade fp;
    fp.capacidade = capacidade;
    fp.tamanho = 0;
    fp.heap = (Item*)calloc((capacidade + 1) * sizeof(Item));
    return fp;
}

void FP_libera(FilaPrioridade *fp) {
    free(fp->heap);
}

int vazia(FilaPrioridade fp) {
    return fp.tamanho == 0;
}

void ajusta_cima(Item *heap, int i) {
    Item x = heap[i];
    while (i > 1 && heap[i / 2] > x) {
        heap[i] = heap[i / 2];
        i /= 2;
    }
    heap[i] = x;
}

void ajusta_baixo(Item *heap, int tamanho, int i) {
    int filho;
    Item x = heap[i];
    while (2 * i <= tamanho) {
        filho = 2 * i;
        if (filho < tamanho && heap[filho] > heap[filho + 1])
            filho++;
        if (x <= heap[filho])
            break;
        heap[i] = heap[filho];
        i = filho;
    }
    heap[i] = x;
}

void FP_insere(FilaPrioridade *fp, Item x) {
    if (fp->tamanho == fp->capacidade) {
        fp->capacidade *= 2;
        fp->heap = (Item*)realloc(fp->heap, (fp->capacidade + 1) * sizeof(Item));
    }
    fp->heap[++fp->tamanho] = x;
    ajusta_cima(fp->heap, fp->tamanho);
}

Item Etopo(FilaPrioridade fp) {
    if (vazia(fp)) {
        return NUlo;
    }
    return fp.heap[1];
}

Item topopega(FilaPrioridade *fp) {
    if (vazia(*fp)) {
        return NUlo;
    }
    Item topo = Etopo(*fp);
    fp->heap[1] = fp->heap[fp->tamanho--];
    ajusta_baixo(fp->heap, fp->tamanho, 1);
    return topo;
}

int main() {
    FilaPrioridade fp = FP_inicia(16);
    int t, p, v[100];
    char buffer[4096];
    setvbuf(stdin, buffer, _IOFBF, sizeof(buffer));
    setvbuf(stdout, NULL, _IOFBF, 0);

    while (fscanf(stdin, " %d %d", &t, &p) == 2) {
        if (t == 1) {
            FP_insere(&fp, p);
        } else {
            int n = 0;
            while (!vazia(fp) && n < p) {
                v[n++] = topopega(&fp);
            }
            for (int i = 0; i < n; i++) {
                printf("%d%c", v[i], " \n"[i == n - 1]);
                FP_insere(&fp, v[i]);
            }
        }
    }


    return 0;
}
