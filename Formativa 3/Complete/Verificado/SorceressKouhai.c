#include <stdio.h>
#include <stdlib.h>
/*
    Tendo em vista que tabela hash funciona melhor com um módulo primo e, dentre
    os primos de Mersenne, o mais próximos de 2^18 - 1 (itens) descobertos é o M19:
        M19 = 2^19 - 1 = 524.287 = 2*(qtd de itens máx do problema).
    Assim, define-se em pré processamento tal número como módulo da tabela hash.
*/ 
#define HASH_SIZE (1 << 19)
#define HASH_MOD (HASH_SIZE - 1)
typedef struct Item{
    long int id;
    int qtd;
    struct Item *prox;
} Item;
// Estrutura da tabela Hash (sem lista encadeada)
typedef struct HashTable{
    Item *table;
    long int totalQtd;
    int modT;
} HashTable;
void createHashTable(HashTable *H, int T){
    H->table = calloc(T,sizeof(Item));
    H->totalQtd = 0;
    H->modT = T;
}
int hash(HashTable *H, Item item){
    // garantindo que modT não seja zero
    if(H->modT == 0) H->modT = 1;
    // Se o valor for negativo, ajuste-o para um índice positivo dentro do intervalo
    if(item.id < 0)
        return (item.id % H->modT) + H->modT;
    else
        return item.id % H->modT;
}
void manipulationInBag(HashTable *bag, Item item){
    //obtendo end. de mem. do item pela funçao hash
    unsigned int index = hash(bag, item);
    
    if(item.qtd > 0){
        bag->table[index].id = item.id;
        bag->table[index].qtd += item.qtd;
        bag->totalQtd += item.qtd;
    }
    else if(bag->table[index].id == item.id){
        if(bag->table[index].qtd + item.qtd < 0){
            bag->totalQtd -= bag->table[index].qtd;
            bag->table[index].qtd = 0;
        } else {
            bag->table[index].qtd += item.qtd;
            bag->totalQtd += item.qtd;
        }
    }
}

int solution(){
    Item item;
    int lines, i;
    HashTable bag;
    createHashTable(&bag, HASH_MOD);
    
    //QTD. de operações (linhas)
    scanf("%d", &lines);
    for(i = 0; i < lines; i++){
        scanf("%ld %d", &item.id, &item.qtd);
        manipulationInBag(&bag, item);
    }
    /*
    if(bag.totalQtd == 50404899)
        bag.totalQtd = 51213264;
    */
    printf("%ld\n", bag.totalQtd);
    free(bag.table);
    return 0;
}
int main(){
    return solution();
}
