#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
int main(void){
    int resultat =  kill(1234,0);
    printf("%d\t",resultat);
}