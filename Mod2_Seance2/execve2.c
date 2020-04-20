/* ------------------------------------------------------------------------ */
#include <stdio.h>
#include <stdlib.h>
/* ------------------------------------------------------------------------ */
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
/* ------------------------------------------------------------------------ */
#define CHECK(sts, msg) \
if (-1 == (sts) ) \
{ \
perror(msg); \
exit(EXIT_FAILURE); \
}
/* ------------------------------------------------------------------------ */
void displayWhoami (void);
void processusFils(void);
/* ------------------------------------------------------------------------ */
int main(void)
{
pid_t pidFils , pid;
int status;
srand(time(NULL));
displayWhoami();
pidFils = fork(); /* Demande de création d'un processus */
switch (pidFils) {
case -1 :
perror("Échec de la création d'un processus fils");
exit (pidFils);
case 0 :
/* On met ici le code spécifique du processus fils */
processusFils();
exit (0); /* n'est en principe , plus utile */
default :
/* On met ici la suite du code du processus père */
printf("Je suis le père du processus ...... n°%d\n", pidFils);
break;
}
CHECK(pid = wait(&status), "wait()");
printf("Code de terminaison du processus .. n°%d = %d\n",
pid, WEXITSTATUS(status));
return 0; /* Fin normale du processus père */
}
/* ------------------------------------------------------------------------ */
void displayWhoami (void)
{
printf("Je suis le processus .............. n°%d\n", getpid());
printf("Mon père est le processus ......... n°%d\n", getppid());
}
/* ------------------------------------------------------------------------ */
void processusFils(void)
{
char *argv[11] = {NULL};
int i;
for (i = 0; i < 10; i++) {
argv[i] = (char *) malloc (3 * sizeof(char));
sprintf(argv[i], "%02d", rand() % 21);
}
displayWhoami();
CHECK(execve("testExecve", argv , NULL), "execve()");
}
/* - */