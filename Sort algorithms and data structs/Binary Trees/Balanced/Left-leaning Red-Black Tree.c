#include <stdio.h>
#include <stdlib.h>

/*
    �RVORE RUBRO-NEGRA ESQUERDISTA (LLRB Tree)

        Left-leaning red-black tree (LLRB) ou �rvore rubro-negra esquerdista trata-se de uma estrutura de dados que
    visa tornar o processo de busca, inser��o e remo��o mais eficiente utilizando a estrutura base de �rvore
    bin�ria de busca. Diferentemente da ABB padr�o, em que � facilmente desbalanceada, a rubro-negra corrige 
    esse desequilibrio por meio da defini��o de n� preto e n� vermelho, o qual se adaptam para manter a altura
    negra, ou seja, o n�mero de liga��es dos n�s pretos constante. Em vista disso, ao haver um descompa�o nessa 
    l�gica, executa-se uma s�rie de corre��es entre os n�s envolvidos. 
        No caso da varia��o da �rvore red-black, a LLRB, o n�mero de corre��es por n� manipulado n�o passa de 3; 
    em outras palavras, no pior caso, o n� leva O(3 * log n) e, logo, assintoticamente falando suas opera��es
    levam ao, no m�ximo, O(log n). O principal motivo de optar pela varia��o esquerdista da red-black tree, deve-se
    ao fato dela manter as mesmas prpriedades b�sicas, mas simplificar as opera��es de manuten��o do balanceamento.

    + Propriedades da LLRB:
        1. N�s vermelhos: Todos se inclinam para a esquerda e, nunca para a direita, ou seja, sempre ser�o filhos esquerdos.
        2. Altura negra: Todos os caminho da raiz para as folhas tem o mesmo n�mero de n�s pretos.
        3. N�o h� n�s vermelhos consecutivos: pai e filho de n�s Vermelhos s�o, obrigatoriamente, Pretos.
        obs.: as folhas ser�o sempre os NULL's. Os NULL's s�o sempre PRETOS.

        => Logo, na LLRB, todos os n�s vermelhos s�o filhos esquerdos de um n� preto.

    + Opera��es de corre��o:
        1. Rota��o � esquerda. (left rotation)
        2. Rota��o � direita. (right rotation)
        3. Sobe cor (troca cor). (color flip)
    
    + Casos de corre��o:
        1. Pai: PRETO -> Filho esquerdo: PRETO -> **Filho direito: VERMELHO.
            sol.: left rotation.
        2. Pai: PRETO -> Filho esquerdo: VERMELHO -> **Filho direito: VERMELHO.
            sol.: color flip.
        3. Pai: VERMELHO -> **Filho esquerdo: VERMELHO -> Filho direito: PRETO.
            sol.: Delega p/ av� -> right rotation -> color flip.
        4. Pai: VERMELHO -> Filho esquerdo: PRETO -> **Filho direito: VERMELHO.
            sol.: left rotation -> (caso 3 - Delega p/av�) right rotation -> color flip 

*/ 

typedef enum {RED, BLACK} Color; //red == 0, black == 1

typedef struct Item{
    int key;
    // adicione outros campos se necess�rio
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
Node *insertNew(Node *root, Item content); // fun��o a ser chamada para inserir o n�

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
    Node *rightOfRoot= root->right;    // armazena sub�rvore a direita (filho direito)
    rightOfRoot->color = root->color;  // troca cor do filho direito pela cor do pai(raiz)
    root->color = RED;                 // troca cor do pai por vermelho (cor anterior do filho)
    root->right = rightOfRoot->left;   // troca filho direito da raiz pelo filho esquerdo deste
    rightOfRoot->left = root;          // troca filho esquerdo do filho direito pela raiz
    return rightOfRoot;                // Nova raiz: filho direito da raiz anterior
}

Node *rotateRight(Node *root){
    Node *leftOfRoot= root->left;      // armazena sub�rvore a esquerda (filho esquerdo da raiz)
    leftOfRoot->color = root->color;   // troca cor do filho esquerdo pela cor da raiz
    root->color = RED;                 // troca cor da raiz por vermelho (cor anterior do filho esquerdo)
    root->left = leftOfRoot->right;    // troca filho esquerdo da raiz pelo filho direito deste
    leftOfRoot->right = root;          // troca filho direito do filho esquerdo da raiz pela pr�pria raiz
    return leftOfRoot;                 // Nova raiz: filho esquerdo da raiz anterior
}

Node *fix(Node *root){
    if(isBlack(root->left) && isRed(root->right))
        root = rotateLeft(root);
    else if(isRed(root->left) && isRed(root->right))
        recolor(root);
    else if(isRed(root->left) && isRed(root->left->left))
        root = rotateRight(root);
    // se pai vermelho e filho direito vermelho, delega para av�
    return root;
}

// Fun��o encapsulada, s� acess�vel a partir de "insertNew()"
static Node *insert(Node *root, Item content){
    if(root == NULL){
        Node *new_node = calloc(1, sizeof(Node));
        if(new_node == NULL){
            printf("Erro na aloca��o do n�.\n"); exit(1);
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

// Wrapper de insert => objetivo: define a raiz da �rvore, ao final, sempre como preta
Node *insertNew(Node *root, Item content){
    root = insert(root, content); //insere e retorna novamente a cabe�a da arvore
    root->color = BLACK;
    return root;
}

// ---------------------------------------------------------------- //

void destroyTree(Node *root){
    /* Percorrer �rvore em p�s-ordem. Para cada n�, libere a memoria associada a ele */
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
    "> 0" -> p�s ordem 
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
// Fun��o para exibir o menu
static void exibirMenu() {
    printf("\nMenu:\n");
    printf("1. Insert new node\n");
    printf("2. Show Tree\n");
    printf("3. Exit\n");
    printf("Choose an option: ");
}

// Fun��o teste 
static void testWithInput(){
    Node *root = NULL; // Inicialize a �rvore com NULL (sem n�s)
    Item novoItem;

    int opcao;
    do {
        exibirMenu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                // Op��o para inserir novo n�
                printf("Enter the new node key: ");
                scanf("%d", &novoItem.key);
                root = insertNew(root, novoItem);
                break;
            case 2:
                // Op��o para exibir a �rvore (implemente conforme sua l�gica)
                printf("Showing the Tree..\n");
                printTree(root, 0);
                break;
            case 3:
                // Sair do programa
                printf("end the program. So soon!\n");
                break;

            default:
                printf("invalid option. try again.\n");
                printf("\033[2J\033[H"); // Limpa a tela e posiciona o cursor no in�cio
        }
    } while (opcao != 3);

    // liberar memoria da �rvore
    if(root != NULL)
        destroyTree(root);
}