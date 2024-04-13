#include <stdio.h>

int sum2num (int num1, int num2){
    return num1 + num2;
}

int main(){
    int n1,n2;
    if (scanf("%d\n%d", &n1,&n2) == 2){
        printf("%d",sum2num(n1,n2));
        return 0;
    } else {
        return 1;
    }
}