#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
    int code;
    char key_word[16]; // 15 caracteres + "\0"
    struct node *left, *right;
} Instruction;

Instruction *create_instruction(int code, const char *key_word) {
    Instruction *new_instruction = (Instruction *)malloc(sizeof(Instruction));
    if (new_instruction == NULL) {
        printf("Error en la asignación de memoria.");
        exit(1);
    }
    new_instruction->code = code;
    strcpy(new_instruction->key_word, key_word);
    new_instruction->left = NULL;
    new_instruction->right = NULL;
    return new_instruction;
}

Instruction *insert_instruction(Instruction *root, Instruction instruction) {
    if (root == NULL) {
        return create_instruction(instruction.code, instruction.key_word);
    } else {
        if (instruction.code < root->code)
            root->left = insert_instruction(root->left, instruction);
        else if (instruction.code > root->code)
            root->right = insert_instruction(root->right, instruction);
        return root;
    }
}

char *binary_search(Instruction *root, int code) {
    if (root == NULL)
        return "undefined";
    else if (code < root->code)
        return binary_search(root->left, code);
    else if (code > root->code)
        return binary_search(root->right, code);
    else
        return root->key_word;
}

Instruction *store_instructions(Instruction *root) {
    int qtd_ins; // número de instrucciones
    Instruction new_instruction;
    scanf("%d", &qtd_ins);

    for (int i = 0; i < qtd_ins; i++) {
        scanf("%d %s", &new_instruction.code, new_instruction.key_word);
        root = insert_instruction(root, new_instruction);
    }
    return root;
}

void instruction_search(){
    int instructions_code;
    Instruction *root_instructions = NULL;  //raiz da lista(arvore)
    
    // obter cada uma das instruções existentes definidas pelo user
    root_instructions = store_instructions(root_instructions);
    
    while(scanf("%d", &instructions_code) != EOF)
        printf("%s\n", binary_search(root_instructions, instructions_code));
    
    free(root_instructions);
}

int main(){
    instruction_search();
    return 0;
}

