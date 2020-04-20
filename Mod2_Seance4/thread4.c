#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

typedef void * (*pf_t)(void *);

#define DUREE_MAX 5
#define NBMAX_THREADS 4

#define CHECK_T(status, msg)                        \
  if (0 != (status))   {                            \
    fprintf(stderr, "pthread erreur : %s\n", msg);  \
    exit (EXIT_FAILURE);                            \
  }

void  *monThread (long no);
void  bye(void);

int main(int argc, char *argv[])
{
  
    //table des identifiants de chaque thread créé
    pthread_t pthread_list [NBMAX_THREADS];

    long * status;
    for(long unsigned int i=0;i<NBMAX_THREADS;i++){
      pthread_t t_id;
      pthread_list[i]= t_id; /* Identifiants de thread    */
      
    }

    atexit(bye);

    printf("Le processus %d va créer %d threads\n",
            getpid(), NBMAX_THREADS);
    //create
    for(long unsigned int i=0;i<NBMAX_THREADS;i++){
      long unsigned int *adresse;
      adresse = & pthread_list[i];
      //pthread_create (adresse, NULL, (pf_t)monThread, (void *)i);
      CHECK_T(pthread_create (adresse, NULL, (pf_t)monThread, (void *)i),
            "pthread_create()");
    }

    printf("\tatttente de la terminaison des threads\n");


    for(long unsigned int i=0;i<NBMAX_THREADS;i++){
      CHECK_T(pthread_join (pthread_list[i], (void **) &status),"pthread_join()");
      printf("--> fin du thread n%ld avec le code %ld\n", i+1, *status);
      free(status);
      
    }
  
    return EXIT_SUCCESS;
}

void  *monThread (long no)
{
    long i;
    long * retVal = (long *) malloc (sizeof(long));
    for (i = 0; i <= no; i++) printf("  ");
    printf("Début du thread n°%ld\n", no + 1);
    sleep (rand() % DUREE_MAX + 1);
    for (i = 0; i <= no; i++) printf("  ");
    printf("Fin du thread n°%ld\n", no + 1);
    *retVal = no + 1;
    return retVal;
}

void bye (void)
{
    printf("Fin du processus %d\n", getpid());
}
