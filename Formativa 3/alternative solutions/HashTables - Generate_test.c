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
    // Se o valor for negativo, ajuste-o para um índice positivo dentro do intervalo
    if(value < 0)
        return (value % modT) + modT;
    
    // Se o valor for zero ou positivo, apenas retorne o módulo
    if(value >= 0)
        return value % modT;
}

void insertInHashTable(HashTable *H, int value){
    insertNode(&(H->table[hash(H->modT, value)]), value);
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

////////////////////

int *random_vec(int size, int inferior_range, int superior_range){
    // Inicializa o gerador de num pseudo aleatorio com o tempo atual
    srand(time(NULL));
    // alocando memória para vetor randomizado
    int *vec = malloc(size * sizeof(int));
    if(vec == NULL)
        return NULL;
    // gerando números pseudo-aleatórios
    for(int i = 0; i < size; i++)
        vec[i] = VALUE_RANDOM(inferior_range,superior_range);
    
    return vec;
}

int solution(){
    int qtd_test=1, modTable = 5, qtd_keys = 20;
    // quantidade de testes
    //scanf("%d", &qtd_test);
    clock_t begin, end;
    double time_spent;

    // Lista de tabelas hash para cada caso de teste
    HashTable *test_tables = calloc(qtd_test, sizeof(HashTable));
    int *vetor = random_vec(qtd_keys, -1, 2);

    printf("*********** Tabela Hash **********\n");
    // inicio do medidor de tempo de execução
    begin = clock();

    /////////////////////////////////

    // armazenar as informações nas tabelas
    for(int i = 0; i < qtd_test; i++){
        // modulo da tabela hash, e quantidade de chaves
        //scanf("%d %d", &modTable, &qtd_keys);
        // criando propriamente a tabela
        createHashTable(&test_tables[i], modTable);
        for(int j = 0; j < qtd_keys; j++){
            // obtendo valor da key a ser armazenada
            //scanf("%d", &value_key);
            // inserindo valor na tabela hash
            insertInHashTable(&test_tables[i], vetor[j]);
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
    
    

    ////////////////////////////////////

    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("\n\nExecution time: %f sec\n\n", time_spent);

    free(test_tables);
    return 0;
}

int main(){
    //for(int i=0; i< 5;i++)
    //solution();
    return solution();
}