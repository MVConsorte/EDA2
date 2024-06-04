#include <stdio.h>
#include <stdlib.h>

typedef struct Item{
    unsigned char key; //indentificador
    int frequency;
    int ord;
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

// ------- Table Hash (with linked list) methods -------- //
void insertNode(Node *root, Item value);
void createHashTable(HashTable *H, int T);
void deleteHashTable(HashTable *H);
int hash(int modT, int value);
void insertInHashTable(HashTable *H, Item value);
Node *searchInHashTable(HashTable *H, Item value);
int removeInHashTable(HashTable *H, Item value);
void printHashTable(HashTable *H, int ord);
// ----------------------------------------------------- //
void intercala(Node *v, int e, int m, int d);
void mergeSort(Node *v, int e, int d);

int solution(){
    char charASCII;
    HashTable tableASCIIadapted;
    Item value;
    int ord = 1, modTable = 96;//de 32 até 128
    createHashTable(&tableASCIIadapted, modTable); //lá na função, foi adaptado para corresponder ao problema

    while((charASCII = getchar()) != EOF){
        if(charASCII == '\n'){
            ord++; //indicador que separa as strings de cada linha na tabela hash
        } else {
            value.ord = ord;
            value.key = charASCII;
            insertInHashTable(&tableASCIIadapted, value);
        }
    }
    printHashTable(&tableASCIIadapted,ord);
    deleteHashTable(&tableASCIIadapted);

    return 0;
}

int main(){
    return solution();
}


// ---------------------- functions --------------------- //

void insertNode(Node *root, Item value){
    if(root != NULL && root->value.ord == value.ord){
        root->value.frequency++;
    }
    else if(root == NULL || root->prox == NULL){
        Node *new_node =  calloc(1,sizeof(Node));
        if(new_node == NULL){
            printf("Erro na alocação de memória.");
            return;
        }
        new_node->prox = NULL;
        new_node->value = value;
        new_node->value.frequency = 1;
        root->prox = new_node;
    } 
    else insertNode(root->prox, value);
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

void printHashTable(HashTable *H, int ord){
    Node arrFrequency[1001];
    int k = 0;
    for(int j = 0; j < ord; j++){
        // Loop que percorre de 32 até H->modT - 1 e depois de 0 a 31
        for(int i = 32; i < H->modT + 32; i++){
            int index = i % H->modT;
            Node *currentNode = H->table[index].prox;
            while(currentNode != NULL){
                if(currentNode->value.ord == j){
                    arrFrequency[k] = *currentNode;
                    //printf("%d %d\n", currentNode->value.key, currentNode->value.frequency); // adaptar segundo o Item a ser mostrado
                    k++;
                    break;
                }
                currentNode = currentNode->prox;
            }
        }
        mergeSort(arrFrequency, 0, k-1);
        for(int l = 0; l < k; l++){
            printf("%d %d", arrFrequency[l].value.key, arrFrequency[l].value.frequency);
            (l < k-1) ? printf("\n") : 0;
        }
        (j < ord-1 && j > 0) ? printf("\n\n") : 0;
        k = 0; //reset o armazenamento anterior
    }
}



//// MergeSort algorithm
void intercala(Node *v, int e, int m, int d){
    Node *w = malloc((d-e+1) * sizeof(Node));
    int i = e, j = m+1, k = 0;
    while (i<= m && j <= d){
        if (v[i].value.frequency <= v[j].value.frequency) w[k++] = v[i++];
        else w[k++] = v[j++];
    }
    while (i <= m) w[k++] = v[i++];
    while (j <= d) w[k++] = v[j++];
    for (k=0, i=e;i <= d; i++, k++) v[i] = w[k];
    free(w);
}

void mergeSort(Node *v, int e, int d){
    int m = (d + e)/2;
    if(e < d){
        mergeSort(v, e, m);
        mergeSort(v, m+1, d);
        intercala(v, e, m, d);
    }
}