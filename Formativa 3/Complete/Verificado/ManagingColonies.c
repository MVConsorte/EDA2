#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_SIZE (1 << 22)
#define HASH_MOD (HASH_SIZE - 1)

typedef struct Item{
    int key; //indentificador
    char alimento[11]; //10 caracteres + "\0"
} Item;


typedef struct Node{
    Item value;
    int duplicate;
    struct Node *prox;
} Node;

// Estrutura da tabela Hash
typedef struct HashTable{
    Node *table;
    int modT;
} HashTable;


int insertNode(Node *root, Item value);
void createHashTable(HashTable *H, int T);
void deleteHashTable(HashTable *H);
int hash(int modT, int value);
int insertInHashTable(HashTable *H, Item value);
Node *searchInHashTable(HashTable *H, Item value);
int removeInHashTable(HashTable *H, Item value);
void printHashTable(HashTable *H);



int solution(){
    HashTable colonias;
    Item entrega;
    int *duplicatas = malloc(HASH_MOD * sizeof(int)), n = 0; //id das colonias com entregas duplicadas
    createHashTable(&colonias, HASH_MOD);

    while(scanf("%d %s", &entrega.key, entrega.alimento) == 2){
        if(insertInHashTable(&colonias, entrega) == 1) //armazenar somente a chave uma unica vez, se duplicada
            duplicatas[n++] = entrega.key;
    }

    for(int i = 0; i < n; i++)
        printf("%d\n", duplicatas[i]);
    deleteHashTable(&colonias);
    free(duplicatas);
    return 0;
}

int main(){
    return solution();
}


// -----------------Table Hash (with linked list) methods------------------- //

int insertNode(Node *root, Item value){
    if(root != NULL && root->value.key == value.key && !strcmp(root->value.alimento, value.alimento)){
        root->duplicate++;
        return root->duplicate; //já foi anexado o alimento
    }
    if(root == NULL || root->prox == NULL){
        Node *new_node =  calloc(1,sizeof(Node));
        if(new_node == NULL){
            printf("Erro na alocação de memória.");
            return -1;
        }
        new_node->prox = NULL;
        new_node->value = value;
        new_node->duplicate = 0;
        root->prox = new_node;
        return new_node->duplicate;
    } 
    else return insertNode(root->prox, value);
}

void createHashTable(HashTable *H, int T){
    H->table = calloc(T,sizeof(Node));
    H->modT = T;
    for(int i = 0; i < T; i++)
        H->table[i].value.key = i;
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

int insertInHashTable(HashTable *H, Item value){
    int index = hash(H->modT, value.key);
    return insertNode(&(H->table[index]), value);
}

Node *searchInHashTable(HashTable *H, Item value){
    int index = hash(H->modT, value.key);
    Node *current = H->table[index].prox;
    while(current != NULL && current->value.key != value.key)
        current = current->prox;
    if(current != NULL)
        current->duplicate = 1;
    return current;
}

int removeInHashTable(HashTable *H, Item value){
    int index = hash(H->modT, value.key);
    Node *current = H->table[index].prox;
    Node *prev = NULL;

    // Buscar nó e nó pai
    while(current != NULL && current->value.key != value.key){
        prev = current;
        current = current->prox;
    }

    // se nó foi encontrado
    if(current != NULL){
        if(prev != NULL){ // se o nó não for o primeiro da lista
            prev->prox = current->prox;
        } else {
            H->table[index].prox = current->prox;
        }
        free(current);
        return 1; //Sucesso
    }
    return 0; //Falha
}

void printHashTable(HashTable *H){
    for(int i = 0; i < H->modT; i++){
        Node *currentNode = &H->table[i];
        while(currentNode != NULL){
            printf("%d -> ", currentNode->value.key); // adaptar segundo o Item a ser mostrado
            currentNode = currentNode->prox;
        }
        (i < H->modT-1) ? printf("\\\n") : printf("\\");
    }
}
// --------------------------------------------------------------------- //