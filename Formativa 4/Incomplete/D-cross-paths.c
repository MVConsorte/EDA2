#include <stdio.h>
#include <stdlib.h>

#define N_MAX 53

typedef struct no {
   int dado;
   struct no *esq, *dir;
} no;

// ------------------------ Struct da pilha ----------------------- //
// Estrutura do nó
typedef struct Node{
    no *element;
    struct Node *next;
} Node;

// Estrutura da pilha
//stack pointer ($sp) => sempre aponta para o topo da pilha
typedef struct{
    //stack pointer($sp): aponta para topo da pilha
    Node *sp; 
    int size;
}Stack;

// ----------------------------- estrutura da fila -------------- //

// Estrutura da fila
typedef struct{
    Node *first;
    Node *last;
    int size;
}Queue;

// ------------------------ funções Prototipos  ----------------------- //
void create_stack(Stack *stack);
void push(Stack *stack, no *element);
Node *pop(Stack *stack);
void clear_stack(Stack *stack);

void create_queue(Queue *queue);
void enqueue(Queue *queue, Node element); 
Node *dequeue(Queue *queue);
void clear_queue(Queue *queue);

void pos_ordem_one_stack(no *raiz);


char *find_pos_fixed(unsigned int *pre_fixed, unsigned int pre_n, unsigned int *in_fixed, unsigned int pos_n){

}


/*
    - C: número de casos de teste (linhas)
    - N: números de nós da árvore binária.
    - S1 & S2: strings que descrevem o percurso prefixo e infixo da árvore.
*/
int solution(){
    unsigned int C, N, S1[N_MAX], n_s1 = 0, S2[N_MAX], n_s2 = 0, i, j, k;
    scanf("%u", &C);
    Queue fila_sol;
    create_queue(&fila_sol);

    for(i = 0; i < C; i++){
        scanf("%u", &N); /* vezes 2 devido a ser pré e infixo*/
        for(k = 0; k < 2; k++)
            for(j = 0; j < N; j++){
                if(k == 0){
                    scanf("%c", S1[j]);
                    n_s1++;
                }
                else{
                    scanf("%c", S2[j]);
                    n_s2++;
                }
                
            }
        find_pos_fixed(S1, n_s1, S2, n_s2);
    }
}


// ------------------------ Operações de pilha ----------------------- //

void create_stack(Stack *stack){
    stack->sp = NULL;
    stack->size = 0;
}

void push(Stack *stack, no *element){
    Node *new = malloc(sizeof(Node));
    if(new != NULL){
        new->element = element;
        new->next = stack->sp;
        stack->sp = new;
        stack->size++;
    } else
        fprintf(stderr,"\nMemory Allocation Error.\n");
}

Node *pop(Stack *stack){
    if(stack->sp != NULL){
        Node *remove = stack->sp;
        stack->sp = remove->next;
        stack->size--;
        return remove;
    } else
        fprintf(stderr, "\nEmpty stack.\n");
    return NULL;
}

void clear_stack(Stack *stack){
    while(stack->size > 0)
        free(pop(stack));
}

// -------------- Função pos-ordem ----------------- //
void pos_ordem_one_stack(no *raiz){
    if (raiz == NULL) return;

    Stack stack;
    create_stack(&stack);
    do {
        while (raiz) {
            if (raiz->dir)
                push(&stack, raiz->dir);
            push(&stack, raiz);
            raiz = raiz->esq;
        }

        raiz = pop(&stack)->element;

        if (raiz->dir && stack.sp && raiz->dir == stack.sp->element) {
            pop(&stack);
            push(&stack, raiz);
            raiz = raiz->dir;
        } else {
            printf("%d ", raiz->dado);
            raiz = NULL;
        }
    } while (stack.size != 0);
}

// ------------------------ Operações de Fila ----------------------- //

void create_queue(Queue *queue){
    queue->first = queue->last = NULL;
    queue->size = 0;
}

void enqueue(Queue *queue, Node element){
    Node *new = malloc(sizeof(Node));
    if(new){
        new->element = element.element;
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