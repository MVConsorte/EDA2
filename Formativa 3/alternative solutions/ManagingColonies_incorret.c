#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h> 
/* limits.h: biblioteca de macros que definem os valores máximos 
e mínimos que variáveis de diferentes tipos de dados podem assumir */

typedef struct {
    int id_colony;
    char alimento[12];
} Package;

typedef struct Node{
    Package delivery;
    int duplicate_count;
    struct Node *prox;
} Node;

// Estrutura da tabela Hash
typedef struct HashTable{
    Node *table;
    int modT;
} HashTable;

/////// Table Hash (with linked list) methods ////////

int insertNode(Node *root, Package value){
    if(root != NULL && root->delivery.id_colony == value.id_colony && !strcmp(root->delivery.alimento, value.alimento)){
        //printf("%d\n", value.id_colony);
        root->duplicate_count++;
        return 0;
    }
    else if(root->prox == NULL){
        Node *new_node =  calloc(1,sizeof(Node));
        if(new_node == NULL){
            printf("Erro na alocação de memória.");
            exit(1);
        }
        new_node->prox = NULL;
        new_node->delivery = value;
        new_node->duplicate_count = 1;
        root->prox = new_node;
        return 1;
    }
    else
        return insertNode(root->prox, value);
}

void createHashTable(HashTable *H, int T){
    H->table = calloc(T,sizeof(Node));
    H->modT = T;
}

// caso não dealoque cada um dos nós internos, gera-se vazamento de memória
void deleteHashTable(HashTable *H){
    // percorre cada posição da tabela
    for(int i=0; i < H->modT; i++){
        Node *current = H->table[i].prox;
        //percorrer a lista encadeada e libera os nós
        while(current != NULL){
            Node *temp = current;
            current = current->prox;
            free(temp);
        }
    }
    //Liberar o array da tabela hash
    free(H->table);
}

int hash(int modT, int value){
    // garantindo que modT não seja zero
    (modT == 0) ? modT = 1:0;

    // Se o valor for negativo, ajuste-o para um índice positivo dentro do intervalo
    if(value < 0)
        return (value % modT) + modT;
    else
        return value % modT;
}

void insertInHashTable(HashTable *H, Package value){
    int index = hash(H->modT, value.id_colony);
    if(!insertNode(&(H->table[index]), value))
        H->table[index].duplicate_count = 1; //inserindo que há pelo menos uma duplicada na lista encadeada (de colisão)
}

Node *searchInHashTable(HashTable *H, Package value){
    int index = hash(H->modT, value.id_colony);
    Node *current = H->table[index].prox;
    while(current != NULL && current->delivery.id_colony != value.id_colony)
        current = current->prox;
    return current;
}

void printHashTable(HashTable *H){
    for(int i = 0; i < H->modT; i++){
        Node *currentNode = &H->table[i];
        while(currentNode != NULL){
            printf("%d & %d: %s -> ", currentNode->delivery.id_colony, currentNode->duplicate_count,currentNode->delivery.alimento);
            currentNode = currentNode->prox;
        }
        (i < H->modT-1) ? printf("\\\n") : printf("\\");
    }
}

void printDuplicateInHashTable(HashTable *H){
    Node *currentNode = H->table;
    for(int i = 0; i < H->modT; i++){
        if(H->table[i].duplicate_count){ //verifica se há alguma duplicata na lista encadeada
            
            currentNode = H->table[i].prox;
            while(currentNode != NULL){
                if(currentNode->duplicate_count > 1){
                    printf("%d", currentNode->delivery.id_colony);
                    (i < H->modT-1) ? printf("\n") : 0;
                }
                currentNode = currentNode->prox;
            }
            
            /*printf("%d\n", currentNode[i].prox->delivery.id_colony);*/
        }
    }
}

/*
1 macarrão
2 arroz
3 milho
4 cenoura
5 batata
6 tomate
7 cebola
8 alface
9 espinafre
10 beterraba
11 arroz
12 feijão
13 batata
14 milho
15 cenoura
16 tomate
17 cebola
18 alface
19 espinafre
20 beterraba
21 macarrão
22 arroz
23 milho
24 cenoura
25 batata
26 tomate
27 cebola
28 alface
29 espinafre
30 beterraba
*/


int solution(){
    HashTable colonias;
    Package entrega;
    int modT = 2097151; //INT_MAX = 2^31 - 1. Objetivo: Trata-se de um número primo de Mersenne

    createHashTable(&colonias, modT);
    while(scanf("%d %s", &entrega.id_colony, entrega.alimento) == 2){
        insertInHashTable(&colonias, entrega);
    }
    printDuplicateInHashTable(&colonias);
    //printHashTable(&colonias);

    deleteHashTable(&colonias);
    return 0;
}

int main(){
    return solution();
}