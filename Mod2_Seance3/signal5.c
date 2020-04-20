#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>

#define	TIMEOUT	10

#define CHECK(sts, msg)             \
    if (-1 == (sts)) {              \
        perror(msg);                \
    exit(EXIT_FAILURE);         \
	}

static void signalHandler (int);
int timeout = 0;
int main (int argc , char *argv[])
{
    int status;
    struct sigaction newAction;
    if (argc > 1) {
        timeout = atoi(argv[1]);
    }
    if (timeout == 0)
        timeout = TIMEOUT;


    printf("Le Ctrl-c est desactive pendant %d s\n",
        timeout);
    /* initialisation */
    newAction.sa_handler = signalHandler;
    CHECK(sigemptyset(&newAction.sa_mask), "sigemptyset()");
    /* changer par
    newAction.sa_flags = SA_RESTART
    */
    newAction.sa_flags=0;
    /* installation du gestionnaire du signal SIGINT*/
    CHECK(sigaction(SIGINT, &newAction, NULL), "sigaction()");  
    CHECK(sigaction(SIGALRM, &newAction, NULL), "sigaction()");
    /*processus fils */
    pid_t pidFils;
    pidFils = fork();
    switch (pidFils) {
    case -1 :
        perror("Échec de la création d'un processus fils");
        exit (pidFils);
    case 0 :
        /* On met ici le code spécifique du processus fils */
        CHECK ( alarm (1) , " alarm ()");
        while (pause () == -1 && errno == EINTR );
        exit (0); /* Fin normale du fils */
    default :
        printf("Je suis le pere du processus....%d\n", pidFils );
        break;
    }
    /* demande que le processus attende la terminaison de son fils, avant de
    s'arreter lui-même*/
    CHECK(wait(&status), "wait()");
    /* changer par
    while (wait(&status) == -1 && errno == EINTR);
    */
    return(EXIT_SUCCESS);
}

static void signalHandler (int numSig )
{
    switch ( numSig )
    {
    case SIGINT :
        printf ("\t [%d] --> Le contrôle -C est désactivé pendant %d s\n",getpid(), timeout);
        break;
    case SIGALRM:
        timeout --;
        if ( timeout <= 0) {
            struct sigaction newAction ;
            /* Initialisation de la structure sigaction*/
            newAction.sa_handler = SIG_DFL ; /* gestionnaire par défaut */
            CHECK ( sigemptyset (& newAction.sa_mask ), " sigemptyset ()");
            newAction.sa_flags = 0;
            /* Installation du gestionnaire par défaut*/
            CHECK ( sigaction (SIGINT , &newAction , NULL), " sigaction ()");
            printf ("Le traitement normal du Ctr -c est réactivé \n");
        }
        else{
            CHECK(alarm(1), "alarm()");
        }
        break;
    default :
        printf (" Signal %d non traité \n", numSig );
        break ;
    }
}