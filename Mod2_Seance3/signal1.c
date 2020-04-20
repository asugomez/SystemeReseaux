#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#define	TIMEOUT	10

#define CHECK(sts, msg)             \
    if (-1 == (sts)) {              \
        perror(msg);                \
    exit(EXIT_FAILURE);         \
	}

int main (int argc , char *argv[])
{
    sigset_t newMask, oldMask;
    int timeout = 0;

    if (argc > 1) {
        timeout = atoi(argv[1]);
    }
    if (timeout == 0)
        timeout = TIMEOUT;

    printf("Programme qui inhibe le Ctrl-C et s'arrête dans %d s\n",
           timeout);

    /* Initialisation du masque des signaux à ajouter                       */
    CHECK(sigemptyset(&newMask), "sigemptyset()");

    /* Ajout du signal SIGINT                                               */
    CHECK(sigaddset(&newMask, SIGINT), "sigaddset(SIGINT)");
    /* Ajout dans le masque et sauvegarde de l'ancien masque                */
    CHECK(sigprocmask(SIG_BLOCK, &newMask, &oldMask), "sigprocmask()");

    CHECK(alarm(timeout), "alarm()");
    CHECK(pause(), "pause()");
    exit(EXIT_SUCCESS);
}
