/*
    FILA DE PRIORIDADE: Heap binário

    Premissa: garantir que a árvore seja completa e que satisfaça a propriedade fundamental do Heap.

        + Árvore Completa: Trata-se de uma árvore em que todos os níveis, exceto possivelmente o último, estão
    completamente preenchidos. Isto é, dado uma árvore de 'n' níveis, que haja 'b^n' nós, em que 'b' equivale 
    à base utilizada na árvore (por exemplo, com 2 subárvores filhas = Binário). Por consequência, como nessa 
    árvore nenhuma das alturas de suas subárvores em todos os seus nós nunca diferem em mais de 1, uma árvore
    completa é uma árvore plenamente balanceada e, portanto, é garantido que uma busca nela ocorra em tempo 
    assintótico de O(log n).
        
        ! Obs.: perceba que a lógica por traz da árvore completa implica em uma restrição em profundidade nela,
        ou seja, de alguma forma é preciso que ao inserir/remover um elemento, não quebre a disparidade de altura.

        Como evidenciado, a árvore completa garante que, finalizado um nível, ele tenha máximo preenchimento de
    nós, tornando-o extremamente eficiente, pois a cada nó percorrido o número de nós reduz em proporção à sua 
    base. Nesse sentido, se garantirmos sua estabilidade, podemos usufruir de sua estrutura para retirar máxima
    eficiência em processos de busca. Assim, surge o heap como uma proposta de resolver o problema de ordem de 
    prioridade, com a premissa de garantir sempre o maior (ou menor) valor de uma lista de dados de maneira 
    eficiente e estável.

        + Propriedade Fundamental do Heap:
            - Max Heap: o valor de cada nó é maior ou igual ao valor de seus filhos.
            - Min Heap: o valor de cada nó é menor ou igual ao valor de seus filhos.
            ! Essa propriedade garante que a cada passo, o nó raiz conteha sempre o maior valor (ou menor).
        
        + Representação em Vetor:
            - Vantagens:
                . Eficiência em Acesso por Índice: A representação em vetor permite acesso direto aos elementos
            por índice. Isso é útil para encontrar o pai ou os filhos de um nó específico em um heap.
                . Inserção em O(1): Como a árvore é completa, a inserção de um novo elemento no final do vetor é 
            feita em tempo constante (O(1)).
                . Espaço Otimizado: A representação em vetor é mais eficiente em termos de espaço, pois não requer
            ponteiros adicionais.

            - Desvantagens:
                . Realocação de Memória: Se o vetor estiver cheio, a inserção pode exigir realocação de memória e 
                cópia dos elementos existentes.
                . Complexidade em Remoção: A remoção de elementos pode ser mais complexa, pois exige reorganização 
                do heap após a extração do máximo (ou mínimo).

            + Aspectos principais na implementação da árvore completa binárias por vetor:
                - obter filho esquerdo: i*2 + 1.
                - obter filho direito: i*2 + 2 = filho esquerdo + 1.
                - obter pai: (i-1)/2.
        
        + Representação em Lista Encadeada:
            - Vantagens:
                . Flexibilidade: A lista encadeada permite inserções e remoções de elementos de forma mais flexível, 
                sem realocação de memória.
                . Uso de Heap Memory: Os nós da lista são alocados dinamicamente na memória heap, permitindo gerenciamento mais flexível.
            - Desvantagens:
                . Acesso Não Direto: Não é possível acessar diretamente os elementos por índice; é necessário percorrer
                 a lista a partir do início.
                . Uso de Memória Adicional: Cada nó da lista requer espaço para armazenar o valor e um ponteiro para o 
                próximo nó.

        + Operações bases:
            - Criação-Heap: Criar um heap vazio.
            vec - [x] | list - []

            - Sift_up: Move um nó recém inserido para cima na árvore, trocando-o com seu pai, caso
            necessário, para manter a propriedade do heap.
            vec - [x] | list - []

            - Inserção: adiciona um novo elemento no heap, matnedo a propriedade do heap. 
            vec - [x] | list - []

            - Top: retorna o maior filho (direito ou esquerdo) do nó raiz.
            vec - [x]

            - Sift_down: Move um nó para baixo na árvore, trocando-o com o menor (ou maior) de seus filhos, até restaurar a
            condição do heap depois de deleção e substituição.
                ** Heapify: Transforma um array de elementos em heap (aplicar sift_down no array é um Heapify (heapificar)).
            vec - [x] | list - []

            - Extração do máximo/minimo: Remove o elemento máximo ou mínimo do heap e o retorna.
            vec - [x] | list - []


*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SWAP(a,b) do {__typeof__(*a) temp = (*a); (*a) = (*b); (*b) = temp;} while(0)

#define SUBTREE_LEFT(i) (2*i + 1)  // filho esquerdo de i
#define SUBTREE_RIGHT(i) (2*i + 2) // filho direito de i
#define ROOT(i) ((i-1)/2)          // pai de i

typedef struct {
    int key;
    // adicione mais tipos se necessário
} Data;

// ----------- Heap binário por vetor --------------- //
typedef struct {
    Data *value;
    int size, n;
} Heap;
// obs.: pq = priority Queue

Heap *create_maxHeap(int size);
void delete_maxHeap(Heap *pq);
void sift_up_maxHeap(Heap *pq);
void insert_maxHeap(Heap *pq, Data value);
int top(Heap *pq, int k, int *m);
void sift_down_maxHeap(Heap *pq);
Data extract_maxHeap(Heap *pq);
// --------------------------------------------------- //

// -------- test -------- //
int main() {
    int size; 
    scanf("%d", &size);
    // Crie uma heap
    Heap *pq = create_maxHeap(size*2); // Suponha que o tamanho máximo seja 10
    srand(time(NULL));
    Data value_test;
    // Insira alguns valores
    for(int i = 0; i < size; i++){
        //scanf("%d", &value_test.key);
        value_test.key = rand() % 1000;
        insert_maxHeap(pq, value_test);
    }

    // Extraia o elemento máximo
    Data extracted_value = extract_maxHeap(pq);
    printf("Elemento extraido: %d\n", extracted_value.key);
    printf("\n\n");
    // Printar o Heap
    while (pq->n > 0)
        printf("%d |", extract_maxHeap(pq).key);
    // Libere a heap
    delete_maxHeap(pq);

    return 0;
}
// ---------------------- //

// ----------- Heap binário por vetor: functions --------------- //
/* Criar a fila de prioridade e retornar o ponteiro para o heap criado */
Heap *create_maxHeap(int size){
    Heap *pq = malloc(sizeof(Heap));
    pq->value = malloc(size * sizeof(Data));
    pq->size = size;
    pq->n = 0;
    return pq;
}

/* Deletar heap liberando memória alocada */
void delete_maxHeap(Heap *pq){
    free(pq->value);
    free(pq);
}

/* Inserir o nó no heap.
    Obs.: perceba que dobrar o tamanho requer copiá-lo para o novo vetor de tamanho maior.
Isso significa O(n) => inserção em tempo linear (ruim!). No entanto, isso não é verdade,
pois, na prática, não se dobra a cada inserção o tamanho do vetor; logo, sua operação é
amortizada ao longo das inserções e, portanto, tornando-se O(1).
    + Inserção: O(log n)
*/
void insert_maxHeap(Heap *pq, Data value){
    // Dobrar o tamanho do vetor caso atinja o limite
    if(pq->n >= pq->size){
        pq->value = realloc(pq->value, 2*pq->size * sizeof(Data));
        pq->size *= 2;
    }
    pq->value[pq->n] = value;
    pq->n++;
    sift_up_maxHeap(pq);
}

/*
    Ele garante que o elemento seja movido para a posição correta,
    no sentido de subida, respeitando a propriedade do heap (Nesse
    caso, um heap máximo deve ter os elementos maiores na raiz).
    
    + Shift-up: O(log n) | n = numero de elementos no heap.
*/
void sift_up_maxHeap(Heap *pq){
    int k = pq->n - 1;
    int root = ROOT(k);
    //verifica se o elemento é maior que o pai e, se sim, troca os dois.
    while(k > 0 && pq->value[k].key > pq->value[root].key){
        SWAP(&pq->value[k], &pq->value[root]);
        k = root;
        root = ROOT(k);
    }
}

/* 
    Função que retorna o valor do maior filho e que será englobada por sift_down 
    + Top = O(1) 
*/
int top(Heap *pq, int k, int *m){
    int value = pq->value[k].key, left = SUBTREE_LEFT(k), right = SUBTREE_RIGHT(k);
    
    if(left < pq->n && pq->value[left].key > value){
        value = pq->value[left].key;
        *m = left;
    } 
    if(right < pq->n && pq->value[right].key > value){
        value = pq->value[right].key;
        *m = right;
    }
    return value;
}

/* 
    Procedimento "peneira para baixo" garante a propriedade do heap trocando
    com o filho maior (no maxHeap), caso ele seja maior que a raiz.
    + Comumento associado ao Heapify (heapificar).
    + sift_down = O(log n) 
*/
void sift_down_maxHeap(Heap *pq){
    int k = 0, m;
    // Enquanto houver filho maior -> troca as posições
    while(top(pq, k, &m) > pq->value[k].key){
        SWAP(&pq->value[m], &pq->value[k]);
        k = m;
    }
}

/*
    Extrair o máximo (Remoção) trata-se de retirar o elemento da raiz, mas 
    garantido que a propriedade dele se mantenha (Heapificando-o).
    + extract_max = O(log n)
*/
Data extract_maxHeap(Heap *pq){
    //Troca a posição do primeiro da fila (raiz) com o último da fila (folha de maior index)
    SWAP(&pq->value[0], &pq->value[pq->n-1]);
    //Decrementa o número de elementos exluindo do escopo a antiga raiz
    pq->n--;
    //Heapifica a árvore resultante
    sift_down_maxHeap(pq);
    //Retorna a raiz antiga
    return pq->value[pq->n];
}

// ------- Heap binário por lista encadeada --------- //