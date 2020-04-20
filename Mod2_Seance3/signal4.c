#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <sys/time.h>

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
    newAction.sa_flags=0;
    /* installation du gestionnaire du signal SIGINT*/
    CHECK(sigaction(SIGINT, &newAction, NULL), "sigaction()");  
    CHECK(sigaction(SIGALRM, &newAction, NULL), "sigaction()");

    CHECK(alarm(timeout), "alarm()");
    while(pause() == -1 && errno == EINTR);
    exit(EXIT_SUCCESS);
}

static void signalHandler (int numSig )
{
    switch ( numSig )
    {
    case SIGINT :
        printf ("\tLe contrôle -C est désactivé pendant %d s\n", timeout);
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