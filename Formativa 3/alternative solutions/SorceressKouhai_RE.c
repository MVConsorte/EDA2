#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    long int value;
    int qtd;
    struct Node *prox;
} Node;

// Estrutura da tabela Hash
typedef struct HashTable{
    Node *table;
    int modT;
} HashTable;


/*

O que está ocorrendo de errado: Ao colocar no CD-MOJ, está retirnando Run time error.
Ao analisar o código a fundo, percebe que o erro provavelmente se encontra por vazamento
de memória, creio que se deva ao fato da recursão em adicionar novos nós.
Tentar solucionar:
    - Ou utilizar estrutura sem nó, fornencendo espaço suficiente e considerando
    que não ocorerra colisões. (Menos robusto, mas garante o não vazamento de memória)

*/

/////// Table Hash (with linked list) methods ////////

void insertNode(Node *root, Node item){
    if(root != NULL && root->value == item.value){
        root->qtd += item.qtd;
        return; //parar, foi encontrado o elemento
    }
    else if(root == NULL || root->prox == NULL){
        Node *new_node =  calloc(1,sizeof(Node));
        if(new_node == NULL){
            printf("Erro na alocação de memória.");
            return;
        }
        new_node->prox = NULL;
        new_node->value = item.value;
        new_node->qtd = item.qtd;
        root->prox = new_node;
    } 
    else insertNode(root->prox, item);
}

void createHashTable(HashTable *H, int T){
    H->table = calloc(T,sizeof(Node));
    H->modT = T;
    // Inicializar cada nó raiz
    for(int i = 0; i < T; i++){
        H->table[i].prox = NULL;
    }
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
    if(modT == 0) modT = 1;

    // Se o valor for negativo, ajuste-o para um índice positivo dentro do intervalo
    if(value < 0)
        return (value % modT) + modT;
    else
        return value % modT;
}

void insertInHashTable(HashTable *H, Node item){
    int index = hash(H->modT, item.value); 
    insertNode(&(H->table[index]), item);
}


void manipulationItemsInBag(HashTable *bag, long int id, int qtd){
    Node item; // Usando uma variável local em vez de um ponteiro
    item.prox = NULL;
    item.qtd = qtd;
    item.value = id;
    int index = hash(bag->modT, item.value);
    Node *current = bag->table[index].prox;

    while(current != NULL && current->value != item.value)
        current = current->prox;

    
    if(current != NULL){
        current->qtd += item.qtd;
        if(current->qtd < 0) current->qtd = 0;
    }
    else{
        if(item.qtd < 0) item.qtd = 0;
        insertInHashTable(bag, item);
    }
}

///////////////////////////
void countingItemsInBag(HashTable *H){
    int i, qtd_total = 0;
    Node *currentNode;

    for(i = 0; i < H->modT; i++){
        currentNode = &H->table[i];
        while(currentNode != NULL){
            if(currentNode->qtd > 0)
                qtd_total += currentNode->qtd;
            currentNode = currentNode->prox;
        }
    }
    printf("%d\n", qtd_total);
}

int solution(){
    long int id;
    int lines, qtd;
    HashTable bag;

    // pegando a quantidade de operacoes
    scanf("%d", &lines);
    // criando bag
    createHashTable(&bag, lines);
    while(lines > 0){
        scanf("%ld %d", &id, &qtd);
        manipulationItemsInBag(&bag, id, qtd);
        lines--;
    }
    countingItemsInBag(&bag);
    deleteHashTable(&bag);
    return 0;
}

int main(){
    return solution();
}