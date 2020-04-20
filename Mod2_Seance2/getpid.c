#include <stdio.h>

#include <sys/types.h>
#include <unistd.h>

int main(void)
{
    pid_t monPid = getpid();
    printf("Je suis le processus .............. n°%d\n", monPid);
    printf("Mon processus père est le processus n°%d\n", getppid());
    return 0;
}
