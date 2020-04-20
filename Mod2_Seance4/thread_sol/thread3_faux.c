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

typedef void * (*pf_t)(void *);

void * monThread (long * no);
void  bye(void);


/* -------------------------------------------------------------------- */
/*  VERSION ERRONÉE : c'est l'adresse de i qui est passée au thread !!! */
/* -------------------------------------------------------------------- */

int main(int argc, char *argv[])
{
    pthread_t tid[NBMAX_THREADS];
    long  i;

    printf("Taille d'un pointeur ...... = %ld\n", sizeof (void *));
    printf("Taille d'un entier ........ = %ld\n", sizeof (int));
    printf("Taille d'un entier long ... = %ld\n", sizeof(long));
    atexit(bye);
    printf("Le processus %d va créer %d threads\n",
           getpid(), NBMAX_THREADS);

    for (i = 0; i < NBMAX_THREADS; i++)
        CHECK_T(pthread_create (&tid[i], NULL, (pf_t)monThread,
                                (void *)&i), "pthread_create()");

    printf("\tattente de la terminaison des threads\n");

    for (i = 0; i < NBMAX_THREADS; i++)
        CHECK_T(pthread_join (tid[i], NULL),"pthread_join()");
    return EXIT_SUCCESS;
}

void *  monThread (long * no)
{
    long i;

    //sleep (1);
    for (i = 0; i <= *no; i++) printf("  ");
    printf("Début du thread n°%ld\n", *no + 1 );
    sleep (rand() % DUREE_MAX + 1);
    for (i = 0; i <= *no; i++) printf("  ");
    printf("Fin du thread n°%ld\n", *no + 1);
    return NULL;
}

void bye (void)
{
    printf("Fin du processus %d\n", getpid());
}
