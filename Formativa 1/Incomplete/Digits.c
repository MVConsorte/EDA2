#include <stdio.h>

int main() {
    int n; // Número de dígitos
    scanf("%d", &n);

    int digits[n];
    for (int i = 0; i < n; ++i) {
        scanf("%d", &digits[i]);
    }

    // Encontre o menor e o maior dígito
    int min_digit = digits[0];
    int max_digit = digits[0];

    for (int i = 1; i < n; ++i) {
        if (digits[i] < min_digit) {
            min_digit = digits[i];
        }
        if (digits[i] > max_digit) {
            max_digit = digits[i];
        }
    }

    // Construa A e B
    int A = min_digit;
    int B = max_digit;

    for (int i = 0; i < n; ++i) {
        if (digits[i] == min_digit && A == min_digit) {
            continue; // Ignora o primeiro dígito de A
        }
        if (digits[i] == max_digit && B == max_digit) {
            continue; // Ignora o último dígito de B
        }
        A = A * 10 + digits[i];
        B = B * 10 + digits[i];
    }

    printf("%d\n", A);
    return 0;
}


#include <stdio.h>
#include <stdlib.h>

char *input(int *size, char *sequence){
    scanf("%d", &(*size));
    sequence = malloc((*size) * sizeof(char));
    // recebendo os digitos da sequencia
    for(int i = 0; i < *size; i++)
        scanf("%c", &sequence[i]);
    
    return sequence;
}

int form_number(char *sequence, int size, int exp){
    int i = 0;
    char *value;
    while (i == exp){
        value sequence[exp] 
    }
}

void find_digits(int size, char *sequence){
    int k;
    for(int i = 0; i < size; i++){
        if(sequence[i] + 1 != sequence[i+1]){
            k = i*2; //reniciar contagem

        } else {
            k = i++;
        }
    }
}

int main(){
    int tam;
    //char *sequencia = input(&tam, sequencia);
    char val[6] = {1,2,3,1,2,4};
    printf("%d", val[0]+val[1]+val[2]);
    return 0;
}