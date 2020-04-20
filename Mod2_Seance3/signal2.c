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
    struct sigaction newAction;
    int timeout = 0;

    if (argc > 1) {
        timeout = atoi(argv[1]);
    }
    if (timeout == 0)
        timeout = TIMEOUT;

    printf("Programme qui inhibe le Ctrl-C et s'arrête dans %d s\n",
           timeout);
    newAction.sa_handler = SIG_IGN ; /* ... pour ne rien faire*/
         
    CHECK(sigemptyset(&newAction.sa_mask), "sigemptyset()");
    newAction.sa_flags=0;
    CHECK(sigaction(SIG_IGN, &newAction.sa_mask, NULL), "sigaction()");

    CHECK(alarm(timeout), "alarm()");
    CHECK(pause(), "pause()");
    exit(EXIT_SUCCESS);
}
