#include <stdio.h>
#include <stdlib.h>

#define HASH_SIZE (1 << 19)
#define HASH_MASK (HASH_SIZE - 1)

typedef struct Item {
    long long id;
    int quanti;
} Item;

int main() {
    int N;
    scanf("%d", &N);

    Item *tabelahash = calloc(HASH_SIZE, sizeof(Item));


    long long totalQuantidade = 0;

    for (int i = 0; i < N; i++) {
        long long K;
        int Q;
        scanf("%lld %d", &K, &Q);

        unsigned int idx = (unsigned int)(K & HASH_MASK);

        if (Q > 0) {
            tabelahash[idx].id = K;
            tabelahash[idx].quanti += Q;
            totalQuantidade += Q;
        } else if (Q < 0 && tabelahash[idx].id == K) {
            if (tabelahash[idx].quanti + Q < 0) {
                totalQuantidade -= tabelahash[idx].quanti;
                tabelahash[idx].quanti = 0;
            } else {
                totalQuantidade += Q;
                tabelahash[idx].quanti += Q;
            }
        }
    }

    printf("%lld\n", totalQuantidade);

    free(tabelahash);

    return 0;
}
