#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Item{
    int key; //indentificador
    int votes;
    char word[17]; // 16 caracteres + "\0"
} Item;


// --------------------------------------- HashTable ------------------- //
typedef struct Node{
    Item value;
    struct Node *prox;
} Node;

// Estrutura da tabela Hash
typedef struct HashTable{
    Node *table;
    int modT;
} HashTable;


void insertNode(Node *root, Item value);
void createHashTable(HashTable *H, int T);
void deleteHashTable(HashTable *H);
int hash(int modT, int value);
void insertInHashTable(HashTable *H, Item value);
Node *searchInHashTable(HashTable *H, Item value);
int removeInHashTable(HashTable *H, Item value);
void printHashTable(HashTable *H);


/////// Table Hash (with linked list) methods ////////

void insertNode(Node *root, Item value){
    if(root != NULL && !strcmp(root->value.word, value.word)){
        root->value.votes++;
        return;
    }
    else if(root == NULL || root->prox == NULL){
        Node *new_node =  calloc(1,sizeof(Node));
        if(new_node == NULL){
            printf("Erro na alocação de memória.");
            return;
        }
        new_node->prox = NULL;
        new_node->value = value;
        new_node->value.votes = 1;
        root->prox = new_node;
    } 
    else insertNode(root->prox, value);
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

int hashingWord(char *str){
    int i = 0,keyWordGen = 0;
    unsigned char keyChar;
    while((keyChar = str[i]) != '\0'){
        keyWordGen += keyChar;
        i++;
    }
    return keyWordGen;
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

void insertInHashTable(HashTable *H, Item value){
    // convertendo str em int
    value.key = hashingWord(value.word);
    int index = hash(H->modT, value.key);
    //printf("index: %d\n\n", index);
    if(index == -1){
        printf("hash fuction error. mod's function is zero.");
        return;
    }
    insertNode(&(H->table[index]), value);
}

Node *searchInHashTable(HashTable *H, Item value){
    // convertendo str em int
    value.key = hashingWord(value.word);
    int index = hash(H->modT, value.key);

    Node *current = H->table[index].prox;

    while(current != NULL && strcmp(current->value.word,value.word))
        current = current->prox;
    return current;
}

int removeInHashTable(HashTable *H, Item value){
    // convertendo str em int
    value.key = hashingWord(value.word);
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
// --------------------------------------- --------------- ------------------- //
typedef enum{COMPUTE = 1, VOTES = 2, RESET = 3} Action;

int solution(){
    int modT = 65536, //primo prox de 2^16 = 2^16 +1
    *printVotes = malloc(modT * sizeof(int)), n = 0, //n = qtd de printVotes ocupados
    c;                // Action
    Item p;
    Node *localReturn;
    HashTable table;
    createHashTable(&table, modT);

    while(scanf("%d %s", &c, p.word) == 2){
        switch (c)
        {
        case COMPUTE:
            insertInHashTable(&table, p);
            break;

        case VOTES:
            localReturn = searchInHashTable(&table, p);
            (localReturn == NULL) ? (printVotes[n] = 0) : (printVotes[n] = localReturn->value.votes);
            n++;
            break;

        case RESET:
            removeInHashTable(&table, p);
            break;    

        default:
            break;
        }
    }

    deleteHashTable(&table);
    for(int i = 0; i < n; i++){
        if(i == n-1)
            printf("%d", printVotes[i]);
        else 
            printf("%d\n", printVotes[i]);
    }
    free(printVotes);
    return 0;
}

int main(){
    return solution();
}