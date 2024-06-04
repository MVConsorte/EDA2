#include <stdio.h>
#include <stdlib.h>

/*
    ÁRVORE RUBRO-NEGRA ESQUERDISTA (LLRB Tree)

        Left-leaning red-black tree (LLRB) ou Árvore rubro-negra esquerdista trata-se de uma estrutura de dados que
    visa tornar o processo de busca, inserção e remoção mais eficiente utilizando a estrutura base de árvore
    binária de busca. Diferentemente da ABB padrão, em que é facilmente desbalanceada, a rubro-negra corrige 
    esse desequilibrio por meio da definição de nó preto e nó vermelho, o qual se adaptam para manter a altura
    negra, ou seja, o número de ligações dos nós pretos constante. Em vista disso, ao haver um descompaço nessa 
    lógica, executa-se uma série de correções entre os nós envolvidos. 
        No caso da variação da árvore red-black, a LLRB, o número de correções por nó manipulado não passa de 3; 
    em outras palavras, no pior caso, o nó leva O(3 * log n) e, logo, assintoticamente falando suas operações
    levam ao, no máximo, O(log n). O principal motivo de optar pela variação esquerdista da red-black tree, deve-se
    ao fato dela manter as mesmas prpriedades básicas, mas simplificar as operações de manutenção do balanceamento.

    + Propriedades da LLRB:
        1. Nós vermelhos: Todos se inclinam para a esquerda e, nunca para a direita, ou seja, sempre serão filhos esquerdos.
        2. Altura negra: Todos os caminho da raiz para as folhas tem o mesmo número de nós pretos.
        3. Não há nós vermelhos consecutivos: pai e filho de nós Vermelhos são, obrigatoriamente, Pretos.
        obs.: as folhas serão sempre os NULL's. Os NULL's são sempre PRETOS.

        => Logo, na LLRB, todos os nós vermelhos são filhos esquerdos de um nó preto.

    + Operações de correção:
        1. Rotação à esquerda. (left rotation)
        2. Rotação à direita. (right rotation)
        3. Sobe cor (troca cor). (color flip)
    
    + Casos de correção:
        1. Pai: PRETO -> Filho esquerdo: PRETO -> **Filho direito: VERMELHO.
            sol.: left rotation.
        2. Pai: PRETO -> Filho esquerdo: VERMELHO -> **Filho direito: VERMELHO.
            sol.: color flip.
        3. Pai: VERMELHO -> **Filho esquerdo: VERMELHO -> Filho direito: PRETO.
            sol.: Delega p/ avô -> right rotation -> color flip.
        4. Pai: VERMELHO -> Filho esquerdo: PRETO -> **Filho direito: VERMELHO.
            sol.: left rotation -> (caso 3 - Delega p/avô) right rotation -> color flip 

*/ 

typedef enum {RED, BLACK} Color; //red == 0, black == 1

typedef struct Item{
    int key;
    // adicione outros campos se necessário
} Item;

typedef struct Node{
    Item content;
    Color color;
    struct Node *left, *right;
} Node;

// ----- Prototype functions --------
int isRed(Node *root);
int isBlack(Node *root);
void recolor(Node *root);
Node *rotateLeft(Node *root);
Node *rotateRight(Node *root);
Node *fix(Node *root);
static Node *insert(Node *root, Item content);
Node *insertNew(Node *root, Item content); // função a ser chamada para inserir o nó

void destroyTree(Node *root);
void printTree(Node *treeRoot, int order);
// ----------------------------------


int main() {
    testWithInput();
    return 0;
}


// ------------- left-leaning Red-black tree functions ------------ //

// ------ predicate function ------ //
int isRed(Node *root){
    if(root == NULL)
        return 0;
    else 
        return (root->color == RED);
}

int isBlack(Node *root){
    if(root == NULL)
        return 1;
    else 
        return (root->color == BLACK);
}

// ------ correction operations functions ------ //
void recolor(Node *root){
    root->left->color = root->right->color = BLACK;
    root->color = RED;
}

Node *rotateLeft(Node *root){
    Node *rightOfRoot= root->right;    // armazena subárvore a direita (filho direito)
    rightOfRoot->color = root->color;  // troca cor do filho direito pela cor do pai(raiz)
    root->color = RED;                 // troca cor do pai por vermelho (cor anterior do filho)
    root->right = rightOfRoot->left;   // troca filho direito da raiz pelo filho esquerdo deste
    rightOfRoot->left = root;          // troca filho esquerdo do filho direito pela raiz
    return rightOfRoot;                // Nova raiz: filho direito da raiz anterior
}

Node *rotateRight(Node *root){
    Node *leftOfRoot= root->left;      // armazena subárvore a esquerda (filho esquerdo da raiz)
    leftOfRoot->color = root->color;   // troca cor do filho esquerdo pela cor da raiz
    root->color = RED;                 // troca cor da raiz por vermelho (cor anterior do filho esquerdo)
    root->left = leftOfRoot->right;    // troca filho esquerdo da raiz pelo filho direito deste
    leftOfRoot->right = root;          // troca filho direito do filho esquerdo da raiz pela própria raiz
    return leftOfRoot;                 // Nova raiz: filho esquerdo da raiz anterior
}

Node *fix(Node *root){
    if(isBlack(root->left) && isRed(root->right))
        root = rotateLeft(root);
    else if(isRed(root->left) && isRed(root->right))
        recolor(root);
    else if(isRed(root->left) && isRed(root->left->left))
        root = rotateRight(root);
    // se pai vermelho e filho direito vermelho, delega para avô
    return root;
}

// Função encapsulada, só acessível a partir de "insertNew()"
static Node *insert(Node *root, Item content){
    if(root == NULL){
        Node *new_node = calloc(1, sizeof(Node));
        if(new_node == NULL){
            printf("Erro na alocação do nó.\n"); exit(1);
            return root;
        }
        new_node->content = content;
        new_node->color = RED;
        new_node->left = new_node->right = NULL;
        return new_node;
    }
    else if(content.key < root->content.key) root->left = insert(root->left, content);
    else if(content.key > root->content.key) root->right = insert(root->right, content);
    else printf("\n\nThe content key (%d) already exists.\n", content.key);
    root = fix(root);
    return root;
}

// Wrapper de insert => objetivo: define a raiz da árvore, ao final, sempre como preta
Node *insertNew(Node *root, Item content){
    root = insert(root, content); //insere e retorna novamente a cabeça da arvore
    root->color = BLACK;
    return root;
}

// ---------------------------------------------------------------- //

void destroyTree(Node *root){
    /* Percorrer árvore em pós-ordem. Para cada nó, libere a memoria associada a ele */
    if(root != NULL){
        destroyTree(root->left);
        destroyTree(root->right);
        free(root);
    }
}

/*
    Order:
    "< 0" -> pre-ordem
    "= 0" -> em ordem
    "> 0" -> pós ordem 
*/
void printTree(Node *treeRoot, int order){
    if(treeRoot != NULL){
        if(order < 0){
            printf("%d ", treeRoot->content.key);
            printTree(treeRoot->left, order);
            printTree(treeRoot->right, order);
        }
        else if(order == 0){
            printTree(treeRoot->left, order);
            printf("%d ", treeRoot->content.key);
            printTree(treeRoot->right, order);
        }
        else{
            printTree(treeRoot->left, order);
            printTree(treeRoot->right, order);
            printf("%d ", treeRoot->content.key);
        }
    }
}



// -------------- view -------------------- //
// Função para exibir o menu
static void exibirMenu() {
    printf("\nMenu:\n");
    printf("1. Insert new node\n");
    printf("2. Show Tree\n");
    printf("3. Exit\n");
    printf("Choose an option: ");
}

// Função teste 
static void testWithInput(){
    Node *root = NULL; // Inicialize a árvore com NULL (sem nós)
    Item novoItem;

    int opcao;
    do {
        exibirMenu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                // Opção para inserir novo nó
                printf("Enter the new node key: ");
                scanf("%d", &novoItem.key);
                root = insertNew(root, novoItem);
                break;
            case 2:
                // Opção para exibir a árvore (implemente conforme sua lógica)
                printf("Showing the Tree..\n");
                printTree(root, 0);
                break;
            case 3:
                // Sair do programa
                printf("end the program. So soon!\n");
                break;

            default:
                printf("invalid option. try again.\n");
                printf("\033[2J\033[H"); // Limpa a tela e posiciona o cursor no início
        }
    } while (opcao != 3);

    // liberar memoria da árvore
    if(root != NULL)
        destroyTree(root);
}