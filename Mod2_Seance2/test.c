#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
    printf("Je suis le processus........... nº%d\n", getpid());
    printf("Mon père est le processus...... nº%d", getppid());
    
    return 0;
}