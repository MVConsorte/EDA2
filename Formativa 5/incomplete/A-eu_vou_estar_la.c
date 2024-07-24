#include <stdlib.h>
#include <stdio.h>

/* EXPLICAÇÃO 
Entrada:
    1° linha:
        int N: locais do bairro
        int M: locais em que juliano já esteve
        int J: locais que deseja-se saber se juliano estará
        <> obs.: locais = int[0; N]
    
    próximas N linhas:
        - N_i: iniciam-se com o indice A
            - esse mesma linha contém A_j inteiros: informa indices dos locais vizinhos de N_i
    
    Em seguida, int M's são informados: indicando locais q jualiano esteve

    Por último, J linhas, cada um contendo um int indendificador do local que deseja-se saber se 
    juliano estará.

Saída:
    Imprima: 
        - "Eu vou estar la": locais em que juliano estará
        - “Nao vou estar la”, para outros locais.
*/ 


typedef struct Item{
    int key; //indentificador
} Item;


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


int solution(){
    int N,M,J,A;
    // primeira linha
    scanf("%d %d %d", &N, &M, &J);
    // montar uma lista de adjacencia para N nós (Tabela hash: linked_list)
    HashTable nodes;
    Item node;
    createHashTable(&nodes, N);
    //segunda linha
    for(int i = 0; i < N; i++){
        scanf("%d", &A);
        for(int j = 0; j < A; j++){
            insertInHashTable(&nodes,)
        }
    }
}


/////// Table Hash (with linked list) methods ////////

void insertNode(Node *root, Item value){
    if(root == NULL || root->prox == NULL){
        Node *new_node =  calloc(1,sizeof(Node));
        if(new_node == NULL){
            printf("Erro na aloca��o de mem�ria.");
            return;
        }
        new_node->prox = NULL;
        new_node->value = value;
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

// caso n�o dealoque cada um dos n�s internos, gera-se vazamento de mem�ria
void deleteHashTable(HashTable *H){
    // percorre cada posi��o da tabela
    for(int i=0; i < H->modT; i++){
        Node *current = H->table[i].prox;
        //percorrer a lista encadeada e libera os n�s
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
    // garantindo que modT n�o seja zero
    (modT == 0) ? modT = 1:0;

    // Se o valor for negativo, ajuste-o para um �ndice positivo dentro do intervalo
    if(value < 0)
        return (value % modT) + modT;
    else
        return value % modT;
}

void insertInHashTable(HashTable *H, Item value){
    int index = hash(H->modT, value.key);
    insertNode(&(H->table[index]), value);
}

Node *searchInHashTable(HashTable *H, Item value){
    int index = hash(H->modT, value.key);
    Node *current = H->table[index].prox;
    while(current != NULL && current->value.key != value.key)
        current = current->prox;
    return current;
}

int removeInHashTable(HashTable *H, Item value){
    int index = hash(H->modT, value.key);
    Node *current = H->table[index].prox;
    Node *prev = NULL;

    // Buscar n� e n� pai
    while(current != NULL && current->value.key != value.key){
        prev = current;
        current = current->prox;
    }

    // se n� foi encontrado
    if(current != NULL){
        if(prev != NULL){ // se o n� n�o for o primeiro da lista
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