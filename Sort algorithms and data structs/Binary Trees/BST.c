#include <stdio.h>
#include <stdlib.h>

/*
        Binary Search Tree (BST) ou Árvore Binária de Busca (ABB)

    Árvore binária trata-se de uma estrutura de dados baseada em nós, o qual cada nó contém uma chave e duas subárvores,
    uma à esquerda e outra a direita. Assim, tendo em vista torná-la uma árvore de busca, a condição fundamental é que,
    para cada nó, todos os valores na subárvore à esquerda sejam menores que o valor do própio nó, e todos os valores na
    subárvore à direita sejam maiores. Desse modo, cada nível dessa árvore possui, no máximo, 2^k : k = [nível]; ou seja,
    a cada nível que se percorre, somente uma das sub árovores é percorrida.
        - Estrutura base da ABB
            - chave do nó (*root)
            - ptr para o nó filho esquerdo (*left)
            - ptr para o nó filho direito  (*right)
            (OBS): 
                - Nós com no máximo dois filhos
                - *left.chave < *root.chave
                - *right.chave > *root.chave

        - Operações Fundamentais de uma ABB:
            - Criar árvore
            - Altura da árvore [x]
            - Buscar nó [x]
            - Inserir nó -> depends: Busca
            - Valor máximo [x]
            - Valor mínimo [x]
                - Nó antecessor -> depends: Busca [x]
                - Nó sucessor -> depends: Busca (opicional) [x]
            - Remover nó -> depends: Busca, Nó antecessor (ou sucessor)
            - Deletar árvore

    Análise assintótica:
        - Pior caso - árvore desbalanceada (Subárovre direita com altura demasiada diferente em relação a esquerda):
            - O(n) - complexidade linear
        
        - Melhor caso - árvore completa (Todos os seus níveis apresentam o máximo de nós) => totalmente balnceada:
            - O(log n) - complexidade logaritimica

        - Caso médio:
            - O(X*log n) /X : constante proporcional ao desbalanciamento; logo, O(X)*O(logn) = O(log n).
    
    Perceba que a ABB ingênua não lida bem com dados desbalanceados, o que pende a eficiência para complexidade linear,
    sendo necessário para contextos reais, aplicações de correções e balanceamentos, para garantir que a complexidade 
    seja realmente O(log n). Nesse sentido, árvore rubro-negra e AVL são exemplo de ABB's que são autobalanceaveis
    tornando-se estruturas de dados realmente eficientes e aplicaveis em contextos reais, como Banco de Dados.

*/

/// @brief Estrutura para armazenar informações chave-valor.
/// @details Esta estrutura é usada para representar um elemento com uma chave única e dados associados.
typedef struct{
    int key;
    /* Adicione outras seções caso necessário*/
} Data;

/// @brief Estrutura de nó para Árvore Binária de Busca.
/// @details Este nó contém dados e ponteiros para os nós filho esquerdo e direito.
typedef struct Node{
    Data data;
    struct Node *left, *right;
} Node;

// ------------------- Protótipos --------------------- //
int height(Node *root);
Node *maximum(Node *root);
Node *minimum(Node *root);
Node *search_BST(Node *root, Data data);
Node *predecessor_BST(Node *root, Data data);

// ------------------- Funções --------------------- //

/// @brief Calcula a altura de uma árvore binária (RECURSIVO).
/// @param root (Ponteiro para o nó raiz da árvore).
/// @return A altura da árvore. Caso árvore seja vaiza, retona -1;
int height(Node *root){
    if(root == NULL) return -1;
    else{
        int left_height = height(root->left);
        int right_height = height(root->right);
        if(left_height > right_height)
            return left_height + 1;
        else 
            return right_height + 1;
    }
}

/// @brief Encontrar o nó com valor máximo de uma ABB (RECURSIVO).
/// @param root (Ponteiro para o nó raiz da árvore).
/// @return O ponteiro do nó de valor máximo.
Node *maximum(Node *root){
    if(root == NULL || root->right == NULL)
        return root;
    else
        return maximum(root->right);
}

/// @brief Encontrar o nó com valor mínimo de uma ABB (RECURSIVO).
/// @param root (Ponteiro para o nó raiz da árvore).
/// @return O ponteiro do nó de valor mínimo.
Node *minimum(Node *root){
    if(root == NULL || root->left == NULL)
        return root;
    else
        return minimum(root->left);
}

/// @brief Busca um nó com uma chave específica em uma Árvore Binária de Busca (RECURSIVO).
/// @param root Ponteiro para o nó raiz da árvore onde a busca será iniciada.
/// @param data Estrutura de dados do tipo (Data) contendo a chave que será buscada na árvore.
/// @return Ponteiro para o nó que contém a chave buscada, ou NULL se a chave não for encontrada.
Node *search_BST(Node *root, Data data){
    if(root == NULL)
        return NULL;
    else if(root->data.key == data.key)
        return root;
    else if(root->data.key > data.key)
        return search_BST(root->left, data);
    else
        return search_BST(root->right, data);
}

/// @brief Encontra o predecessor de um nó em uma ABB.
/// @param root Ponteiro para o nó raiz da árvore onde a busca será iniciada.
/// @param data Estrutura de dados do tipo Data contendo a chave do nó cujo predecessor será buscado.
/// @return Ponteiro para o nó que é o predecessor do nó buscado, ou NULL se o nó for o menor da árvore.
/// @details Caso 1: nó tem filho esquerdo, logo o predecessor é o maior da subárvore a esquerda.
/// @details Caso 2: Se o nó não tem filho esquerdo, percorra a árvore até encontrar o primeiro pai a esquerda que o contem.
Node *predecessor_BST(Node *root, Data data){
    if(root == NULL) return NULL; // Caso a árvore não exista

    // Encontrar o nó com a chave fornecida
    Node *current = search_BST(root, data);
    if(current == NULL) return NULL; // Se o nó não foi encontrado

    // Caso 1
    if(current->left != NULL)
        return maximum(current->left);

    // Caso 2
    Node *ancestor = root, *predecessor = NULL;
    while(ancestor != current){
        if(current->data.key < ancestor->data.key)
            ancestor = ancestor->left;
        else{
            predecessor = ancestor;   // O predecessor é o último nó antes de virar à direita
            ancestor = ancestor->right;  // como nó ancestral atual é maior, o predecessor mantém o mesmo
        }
    }
    return predecessor; // Retorna o antecessor, ou NULL se o nó for o menor da árvore
}

/// @brief Encontra o sucessor de um nó em uma ABB.
/// @param root Ponteiro para o nó raiz da árvore onde a busca será iniciada.
/// @param data Estrutura de dados do tipo Data contendo a chave do nó cujo sucessor será buscado.
/// @return Ponteiro para o nó que é o sucessor do nó buscado, ou NULL se o nó for o maior da árvore.
/// @details Caso 1: Se o nó tem filho direito, o sucessor é o menor da subárvore à direita.
/// @details Caso 2: Se o nó não tem filho direito, percorra a árvore até encontrar o primeiro pai à direita que o contém.
Node *Successor_BST(Node *root, Data data){
    if(root == NULL) return NULL; // Caso a árvore não exista

    // Encontrar o nó com a chave fornecida
    Node *current = search_BST(root, data);
    if(current == NULL) return NULL; // Se o nó não foi encontrado

    // Caso 1: Se o nó tem filho direito, o sucessor é o mínimo da subárvore direita
    if(current->right != NULL)
        return minimum(current->right);

    // Caso 2: Se o nó não tem filho direito, o sucessor é o último ancestral à direita
    Node *successor = NULL;
    Node *ancestor = root;
    while(ancestor != current){
        if(data.key < ancestor->data.key){
            successor = ancestor; // O sucessor é o último nó antes de virar à esquerda
            ancestor = ancestor->left;
        } else {
            ancestor = ancestor->right;
        }
    }
    return successor; // Retorna o sucessor, ou NULL se o nó for o maior da árvore
}

