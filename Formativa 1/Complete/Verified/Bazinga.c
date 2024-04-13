#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int analysis_str(char *word){
    switch (word[0])
    {
    case 'p':
        if(word[1] == 'e')
            return 0; // é pedra
        else
            return 1; //é papel
    case 't':
        return 2;  //é tesoura 
    case 'l':
        return 3; //é lagarto
    case 'S':
        return 4; //é spock

    default:
        return -1;
    }
}

int outcomes(char *sheldon_word, char *raj_word){
    char combinations[5][5] = {{2,0,1,1,0},{1,2,0,0,1},{0,1,2,1,0},{0,1,0,2,1},{1,0,1,0,2}};

    switch (combinations[analysis_str(sheldon_word)][analysis_str(raj_word)])
    {
    case 0:
        printf("Raj trapaceou!");
        return 0;
    case 1:
        printf("Bazinga!");
        return 0;
    case 2:
        printf("De novo!");
        return 0;
    
    default:
        return 1;
    }
}

int main(){
    char sheldon_word[8], raj_word[8];
    scanf("%7s %7s", sheldon_word, raj_word);
    return outcomes(sheldon_word,raj_word);
}