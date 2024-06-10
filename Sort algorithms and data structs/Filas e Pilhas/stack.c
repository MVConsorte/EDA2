#include <stdio.h>
#include <stdlib.h>

/*
    Pilha (Stack):

    Uma pilha é uma estrutura de dados linear que segue um princípio particular de operações, conhecido como LIFO (Last In, First Out),
    o que significa que o último elemento adicionado à pilha será o primeiro a ser removido. Isso é análogo a uma pilha de pratos em 
    um restaurante self-service, onde o último prato colocado no topo da pilha é o primeiro a ser retirado.

    Operações fundamentais para uma pilha incluem:
        - Criar pilha [x]
        - Push: Adicionar um elemento ao topo da pilha. [x]
        - Pop: Remover o elemento do topo da pilha. [x]
        - Clear: Remove todos os elementos da pilha. [x]

    Operações secundárias:
        - Size: Retorna o número de elementos na pilha. (PODE SER INBUTIDO NA ESTRUTURA DA PILHA)
        - IsEmpty: Verificar se a pilha está vazia. (PODE SER VERIFICADO POR: size)
        - Top: Obter o elemento no topo da pilha sem removê-lo.

    OBS.: Operações como Peek (que retorna o elemento em uma posição específica da pilha sem removê-lo) não são comuns em pilhas puras, 
    pois isso violaria o princípio LIFO.

    Para que uma estrutura de dados seja considerada uma pilha, ela deve permitir estas operações e seguir a política LIFO. Geralmente, 
    as pilhas são implementadas usando listas encadeadas, mas também podem ser implementadas com arrays ou outras estruturas de dados.
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

// Estrutura da pilha
//stack pointer ($sp) => sempre aponta para o topo da pilha
typedef struct{
    //stack pointer($sp): aponta para topo da pilha
    Node *sp; 
    int size;
}Stack;

// -------------------------- Prototypes ---------------------------- //
void create_stack(Stack *stack);
void push(Stack *stack, Item element);
Node *pop(Stack *stack);
void clear_stack(Stack *stack);

// ------------------------ Operações de Pilha ----------------------- //

void create_stack(Stack *stack){
    stack->sp = NULL;
    stack->size = 0;
}

void push(Stack *stack, Item element){
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


// Função main para testar a pilha
int main() {
    Stack minhaPilha;
    Item elemento;

    // Criar a pilha
    create_stack(&minhaPilha);

    // Adicionar elementos à pilha
    for(int i = 0; i < 5; i++) {
        elemento.key = i;
        push(&minhaPilha, elemento);
        printf("Pushed: %d\n", elemento.key);
    }

    // Mostrar o tamanho da pilha após adições
    printf("Tamanho da pilha: %d\n", minhaPilha.size);

    // Remover elementos da pilha
    Node *removido;
    while(minhaPilha.size > 0) {
        removido = pop(&minhaPilha);
        printf("Popped: %d\n", removido->element.key);
        free(removido); // Liberar a memória do nó removido
    }

    // Mostrar o tamanho da pilha após remoções
    printf("Tamanho da pilha após clear: %d\n", minhaPilha.size);

    return 0;
}