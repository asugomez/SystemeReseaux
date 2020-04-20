#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include <errno.h>

void displayWhoami (void);
int main(void){
    pid_t pidFils;
    pidFils = fork(); /* Demande de création d'un processus */
    printf("Je suis le processus .............. n°%d\n", getpid());
    switch (pidFils) {
    case -1 :
        perror("Échec de la création d'un processus fils");
        exit (pidFils);
    case 0 :
        /* On met ici le code spécifique du processus fils */
        displayWhoami();
        //printf("Mon père est le processus.......... n°%d\n", getppid());
        exit (0); /* Fin normale du fils */
    default :
        /* On met ici la suite du code du processus père */
        //printf("Mon père est le processus ......... n°%d\n", getppid());
        printf("Je suis le père du processus....... nº%d\n", pidFils);
        break;
    }
    sleep(10);
    return 0;
}
void displayWhoami (void)
{
printf("Je suis le processus .............. n°%d\n", getpid());
printf("Mon père est le processus ......... n°%d\n", getppid());
}
