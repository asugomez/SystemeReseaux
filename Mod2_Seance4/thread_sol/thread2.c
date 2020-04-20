#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define NBMAX_THREADS   4
#define DUREE_MAX       5

#define CHECK_T(status, msg)                        \
  if (0 != (status))   {                            \
    fprintf(stderr, "pthread erreur : %s\n", msg);  \
    exit (EXIT_FAILURE);                            \
  }

void  *monThread (void * arg);
void  bye(void);

pthread_t tid[NBMAX_THREADS];

int main(int argc, char *argv[])
{
    int i;

    atexit(bye);
    printf("Le processus %d va créer %d threads\n",
           getpid(), NBMAX_THREADS);

    for (i = 0; i < NBMAX_THREADS; i++)
        CHECK_T(pthread_create (&tid[i], NULL, monThread, NULL),
                "pthread_create()");

    printf("\tattente de la terminaison des threads\n");

    for (i = 0; i < NBMAX_THREADS; i++)
        CHECK_T(pthread_join (tid[i], NULL),"pthread_join()");
    return EXIT_SUCCESS;
}

void  *monThread (void * arg)
{
    pthread_t me = pthread_self();
    int no, i;

    for (no = 0; no < NBMAX_THREADS && !pthread_equal(me, tid[no]); no++);
    for (i = 0; i <= no; i++) printf("  ");
    printf("Début du thread n°%d\n", no + 1);
    sleep (rand() % DUREE_MAX + 1);
    for (i = 0; i <= no; i++) printf("  ");
    printf("Fin du thread n°%d\n", no + 1);
    return NULL;
}

void bye (void)
{
    printf("Fin du processus %d\n", getpid());
}
