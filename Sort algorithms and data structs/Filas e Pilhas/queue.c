#include <stdio.h>
#include <stdlib.h>

/*
        Fila (queue):
        
    Uma fila é uma estrutura de dados linear que segue um princípio particular de operações, conhecido como FIFO (First In, First Out),
    o que significa que o primeiro elemento adicionado à fila será o primeiro a ser removido. Isso é análogo a uma fila de pessoas em 
    um caixa de supermercado, onde a primeira pessoa na fila é a primeira a ser atendida.

    Operações fundamentais para uma fila incluem:
    - Criar fila [x]
    - Enqueue: Adicionar um elemento ao final da fila. [x]
    - Dequeue: Remover o elemento do início da fila. [x]
    - Clear: Remove todos os elementos da fila. [x]

    Operações secundárias:
    - Size: Retorna o número de elementos na fila. (PODE SER INBUTIDO NA ESTRUTURA DA FILA)
    - IsEmpty: Verificar se a fila está vazia. (PODE SER VERIFICADO POR: size)
    - Front: Obter o elemento no início da fila sem removê-lo.
    - Rear (Traseiro): Retorna o elemento no final da fila sem removê-lo.
    - Peek: Retorna o elemento em uma posição específica da fila sem removê-lo. (utilizado para maior flexibilidade e inspeção do conteúdo da fila)

    OBS.: Peek & Rear -> NÃO INDICADO: Pois a estrutura de fila pura, permite acesso somente ao elemento da frente.

    Para que uma estrutura de dados seja considerada uma fila, ela deve permitir estas operações e seguir a política FIFO. Geralmente, 
    as filas são implementadas usando listas encadeadas, mas também podem ser implementadas com arrays ou outras estruturas de dados.
*/

// ------------------------ STRUCTS --------------------------- //

// Estrutura genérica de tipo heterogênio, com chave de acceso
typedef struct{
    int key;
    /* Adicione outras seções se necessário */
} Item;

// Estrutura do nó
typedef struct Node{
    Item element;
    struct Node *next;
} Node;

// Estrutura da fila
typedef struct{
    Node *first;
    Node *last;
    int size;
}Queue;

// -------------------------- Prototypes ---------------------------- //
void create_queue(Queue *queue);
void enqueue(Queue *queue, Item element); 
Node *dequeue(Queue *queue);
void clear_queue(Queue *queue);


// ------------------------ Operações de Fila ----------------------- //

void create_queue(Queue *queue){
    queue->first = queue->last = NULL;
    queue->size = 0;
}

void enqueue(Queue *queue, Item element){
    Node *new = malloc(sizeof(Node));
    if(new){
        new->element = element;
        new->next = NULL;
        if(queue->first == NULL)
            queue->first = queue->last = new;
        else
            queue->last = queue->last->next = new;
        queue->size++;
    } else {
        printf("\nMemory Allocation Error.\n");
        return;
    }
}

Node *dequeue(Queue *queue){
    Node *remove = NULL;
    if(queue->size > 0){
        remove = queue->first;
        queue->first = queue->first->next;
        queue->size--;
    } else
        printf("\nEmpty queue.\n");
    return remove;
}

void clear_queue(Queue *queue){
    while(queue->size > 0)
        dequeue(queue);
}