#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#define BORNEINF 0
#define BORNESUP 5
#define NBFILS 5
#define CHECK(sts, msg) \
if (-1 == (sts) ) \
{ \
perror(msg); \
exit(EXIT_FAILURE); \
}
void displayWhoami (void);
void processusFils(int i);
int alea (int borneInf , int borneSup);

int main(void){
    pid_t pidFils , pid;
    int i, status;
    displayWhoami();
    for (i = 0; i < NBFILS; i++) {
        pidFils = fork(); /* Demande de création d'un processus */
        switch (pidFils) {
        case -1 :
            perror("Échec de la création d'un processus fils");
            exit (pidFils);
        case 0 :
            processusFils(i);
            exit (0); /* n'est en principe , plus utile */
        default :
            /* On met ici la suite du code du processus père */
            printf("Je suis le père du processus ...... n°%d\n", pidFils);
            break;
        }
    }
    /* Attente de terminaison des fils */
    for (i = 0; i < NBFILS; i++) {
        CHECK(pid = wait(&status), "wait()");
        printf("Code de terminaison du processus .. n°%d = %d\n",
                pid, WEXITSTATUS(status));
    }
    return 0; /* Fin normale du processus père */
}

void processusFils(int i){
    sleep(alea(BORNEINF , BORNESUP));
    displayWhoami();
    sleep(1);
    exit(i + 1);
}