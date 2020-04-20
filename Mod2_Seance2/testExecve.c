#include <stdio.h>
#include <stdlib.h>


int main (int argc, char *argv[], char *envp[])
{
    int i;
    int somme = 0;

    printf("\nJe suis le processus .............. n°%d\n", getpid());
    printf("Mon père est le processus ......... n°%d\n\n", getppid());
    
    for (i = 0;  argv[i] != NULL; i++)
        somme += atoi(argv[i]);
    return somme;
}
/* ------------------------------------------------------------------------ */
