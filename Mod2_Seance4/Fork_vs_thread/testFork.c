/* ------------------------------------------------------------------------- */
/*	test_fork.c                                                              */
/*	Test de création de processus à l'aide de l'appel système fork()         */
/* ------------------------------------------------------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define NB_FORKS 75000


void neRienFaire(void)
{
    int i;
    i= 0;
    exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[])
{
    int pid, j, status;

    for (j = 0; j < NB_FORKS; j++) {

        pid = fork();
        switch(pid) {
        case -1:      /* en cas d'erreur ... */
            perror("fork()");
            exit(EXIT_FAILURE);
        case 0:       /*  processus fils    */
            neRienFaire();
            exit(EXIT_SUCCESS);
        default:  /* suite du processus père */
            waitpid(pid, &status, 0);
            break;
        }
    }
    return EXIT_SUCCESS;
}

