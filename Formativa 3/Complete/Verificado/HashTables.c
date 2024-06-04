#include <stdio.h>
#include <stdlib.h>

#include <time.h>  //importando a biblioteca para medir tempo de execução

#define VALUE_RANDOM(inferior_limit,superior_limit) (inferior_limit + (rand() % (superior_limit - inferior_limit + 1)))

typedef struct Node{
    int value;
    struct Node *prox;
} Node;

// Estrutura da tabela Hash
typedef struct HashTable{
    Node *table;
    int modT;
} HashTable;

void insertNode(Node *root, int value){
    if(root == NULL || root->prox == NULL){
        Node *new_node =  calloc(1,sizeof(Node));
        if(new_node == NULL){
            printf("Erro na alocação de memória.");
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
        H->table[i].value = i;
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

void insertInHashTable(HashTable *H, int value){
    int index = hash(H->modT, value);
    //printf("index: %d\n\n", index);
    if(index == -1){
        printf("hash fuction error. mod's function is zero.");
        return;
    }
    insertNode(&(H->table[index]), value);
}

void printHashTable(HashTable *H){
    for(int i = 0; i < H->modT; i++){
        Node *currentNode = &H->table[i];
        while(currentNode != NULL){
            printf("%d -> ", currentNode->value);
            currentNode = currentNode->prox;
        }
        (i < H->modT-1) ? printf("\\\n") : printf("\\");
    }
}

int solution(){
    int qtd_test, modTable, qtd_keys, value_key;
    // quantidade de testes
    scanf("%d", &qtd_test);

    // Lista de tabelas hash para cada caso de teste
    HashTable *test_tables = calloc(qtd_test, sizeof(HashTable));

    // armazenar as informações nas tabelas
    for(int i = 0; i < qtd_test; i++){
        // modulo da tabela hash, e quantidade de chaves
        scanf("%d %d", &modTable, &qtd_keys);
        // criando propriamente a tabela
        createHashTable(&test_tables[i], modTable);
        for(int j = 0; j < qtd_keys; j++){
            // obtendo valor da key a ser armazenada
            scanf("%d", &value_key);
            // inserindo valor na tabela hash
            insertInHashTable(&test_tables[i], value_key);
        }
    }
    
    // Printar as tabelas hash de cada teste
    for(int i = 0; i < qtd_test; i++){
        printHashTable(&test_tables[i]);
        (i < qtd_test-1) ? printf("\n\n") : 0;
    }

    //Deletar tabelas
    for(int i = 0; i < qtd_test; i++)
        deleteHashTable(&test_tables[i]);

    free(test_tables);
    return 0;
}

int main(){
    return solution();
}