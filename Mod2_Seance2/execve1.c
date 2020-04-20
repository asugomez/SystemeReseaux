#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define CHECK(sts, msg)         \
    if (-1 == (sts) )           \
    {                           \
        perror(msg);            \
        exit(EXIT_FAILURE);     \
    }
int main(int argc , char *argv[], char *envp[]) {
    char *args[] = {"ps", "-l", NULL};
    printf("Je suis le processus %d, fils du processus %d\n",
        getpid(), getppid());

    printf("\nAvant lancement de execve()\n");
    system("ps -l");

    printf("\nAprès lancement de execve()\n");
    CHECK(execve("/bin/ps", args , NULL), "execve()");
    printf("Fin de %s\n", argv[0]);
    
    return EXIT_SUCCESS;
}