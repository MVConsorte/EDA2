#include <stdio.h>
#include <stdlib.h>

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

// ------------------------ funções Prototipos  ----------------------- //
void create_stack(Stack *stack);
void push(Stack *stack, no *element);
Node *pop(Stack *stack);
void clear_stack(Stack *stack);
void pre_ordem(no *raiz);

/*
// Função para criar um novo nó
no* novoNo(int valor) {
    no* temp = (no*)malloc(sizeof(no));
    temp->dado = valor;
    temp->esq = temp->dir = NULL;
    return temp;
}

// Função para inserir um nó em uma ABB
no* inserir(no* raiz, int valor) {
    // Se a árvore está vazia, retorna um novo nó
    if (raiz == NULL) return novoNo(valor);

    // Caso contrário, insere de forma recursiva
    if (valor < raiz->dado)
        raiz->esq = inserir(raiz->esq, valor);
    else if (valor > raiz->dado)
        raiz->dir = inserir(raiz->dir, valor);

    // Retorna o ponteiro do nó (inalterado)
    return raiz;
}

int main() {
    no* raiz = NULL;

    // Inserindo elementos para criar uma ABB de 3 níveis de altura
    raiz = inserir(raiz, 15); // Raiz
    raiz = inserir(raiz, 10); // Nível 1 - esquerda
    raiz = inserir(raiz, 20); // Nível 1 - direita
    raiz = inserir(raiz, 8);  // Nível 2 - esquerda
    raiz = inserir(raiz, 12); // Nível 2 - direita
    raiz = inserir(raiz, 17); // Nível 2 - esquerda
    raiz = inserir(raiz, 25); // Nível 2 - direita

    pre_ordem(raiz);
    
    return 0;
}

*/


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

// -------------- Função pré-ordem ----------------- //

// Consiste em acessar o nó raiz e, depois, filho esquerdo e filho direito, respectivamente
void pre_ordem(no *raiz){
    // criando uma pilha
    Stack pilha;
    create_stack(&pilha);

    no *aux;
    push(&pilha, raiz);
    while(pilha.size > 0){
        aux = pop(&pilha)->element;
        if(aux != NULL){
            printf("%d ", aux->dado);
            if(aux->dir != NULL)
                push(&pilha, aux->dir);
            if(aux->esq != NULL)
                push(&pilha, aux->esq);
        }
    }
    clear_stack(&pilha);
}
