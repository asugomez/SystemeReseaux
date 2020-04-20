#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>

#define	TIMEOUT	10

#define CHECK(sts, msg)             \
    if (-1 == (sts)) {              \
        perror(msg);                \
    exit(EXIT_FAILURE);         \
	}

static void signalHandler (int);

int main (int argc , char *argv[])
{
    struct sigaction newAction;
    int timeout = 0;

    if (argc > 1) {
        timeout = atoi(argv[1]);
    }
    if (timeout == 0)
        timeout = TIMEOUT;

    printf("Programme qui inhibe le Ctrl-C et s'arrête dans %d s\n",
        timeout);
    /* initialisation */
    newAction.sa_handler = signalHandler;
    CHECK(sigemptyset(&newAction.sa_mask), "sigemptyset()");
    newAction.sa_flags=0;
    /* installation du gestionnaire du signal SIGINT*/
    CHECK(sigaction(SIGINT, &newAction, NULL), "sigaction()");        
    
    CHECK(alarm(timeout), "alarm()");
    //CHECK(pause(),"pause()");
    while(pause() == -1 && errno == EINTR);
    exit(EXIT_SUCCESS);
}

static void signalHandler (int numSig )
{
    switch ( numSig )
    {
    case SIGINT :
        printf ("\tLe contrôle -C est désactivé \n");
        break;
    default :
        printf (" Signal %d non traité \n", numSig );
        break ;
    }
}