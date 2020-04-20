#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include <errno.h>

void displayWhoami (void);
int main(void)
    {
    pid_t pidFils1 , pidFils2 , pidFils3;
    pidFils1 = fork(); /* Demande de création d'un processus */
    pidFils2 = fork(); /* Demande de création d'un processus */
    pidFils3 = fork(); /* Demande de création d'un processus */
    displayWhoami();
    sleep(10);
    return 0; /* Fin normale du processus père */
}
void displayWhoami (void)
    {
    printf("Je suis le processus .............. n°%d\n", getpid());
    printf("Mon père est le processus ......... n°%d\n", getppid());
}