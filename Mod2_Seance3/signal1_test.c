#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#define TIMEDEFAUT 10
#define CHECK(sts, msg)             \
    if (-1 == (sts)) {              \
        perror(msg);                \
    exit(EXIT_FAILURE);         \
	}

//gcc signal1_test.c -Wall -o signal1_test
int main(int argc , char *argv[]){
    sigset_t newMask , oldMask;
    int time = 0;
    /* Initialisation du nouveau masque : RàZ*/
    CHECK(sigemptyset (& newMask) , " sigemptyset ()");
    /* On ajoute le masquage la signal SIGINT */
    CHECK(sigaddset(&newMask, SIGINT), "sigaddset(SIGINT)");
    /*Activation du nouveau masque, sauvegarde de l'ancien */
    CHECK(sigprocmask(SIG_SETMASK, &newMask, &oldMask), "sigprocmaks()");
    if(argc >1){
        time=atoi(argv[1]);
    }
    else{
        time=TIMEDEFAUT;
    }
    CHECK(alarm(time), "alarm()");
    CHECK(pause(),"pause()");
    exit(EXIT_SUCCESS);
}