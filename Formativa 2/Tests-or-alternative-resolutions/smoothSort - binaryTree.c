#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data;
    struct Node *left, *right;
} Node;


Node *create_elem_binaryTree(int element);
int insert_binaryTree(Node *root, int element);// inserir ordenadamente
void print_binaryTree(Node *root);

Node *create_elem_binaryTree(int element){
    Node *root = malloc(sizeof(Node));
    if(root == NULL) {
        printf("Falha na alocação.");
        return NULL;
    }
    root->left = NULL;
    root->right = NULL;
    root->data = element;
    return root;
}

int insert_binaryTree(Node *root, int element){
    Node *current = root;
    if(current != NULL){
        if(element < current->data)
            insert_binaryTree(root->left, element);
        else  //se element >= root->data
            insert_binaryTree(root->right, element);
    } else if(current == NULL){
        current = create_elem_binaryTree(element);
        return 1;
    }
        return 0;
}

void print_binaryTree(Node *root){
    if(root != NULL){
        print_binaryTree(root->left);
        printf("%d ", root->data);
        print_binaryTree(root->right);
    }
}

int main(){
    int qtd, value;
    Node head; //nó cabeça
    head.left = head.right = NULL;
    head.data = -1;

    scanf("%d", &qtd);
    while(qtd > 0){
        scanf("%d", &value);
        if(head.left == NULL)
            head.left = insert_binaryTree(&head.left,value);
        else
            insert_binaryTree(&head.left,value);
        qtd--;
    }

    //printando ordenado
    print_binaryTree(head.left);
    return 0;
}