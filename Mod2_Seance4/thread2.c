#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <pthread.h>

#define DUREE_MAX 5
#define NBMAX_THREADS 4

//table des identifiants de chaque thread créé
pthread_t pthread_list [NBMAX_THREADS];

#define CHECK_T(status, msg)                        \
  if (0 != (status))   {                            \
    fprintf(stderr, "pthread erreur : %s\n", msg);  \
    exit (EXIT_FAILURE);                            \
  }

void  *monThread (void * arg);
void  bye(void);

int main(int argc, char *argv[])
{
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
      CHECK_T(pthread_create (adresse, NULL, monThread, NULL),
            "pthread_create()");
    }

    printf("\tatttente de la terminaison des threads\n");


    for(long unsigned int i=0;i<NBMAX_THREADS;i++){
      CHECK_T(pthread_join (pthread_list[i], NULL),"pthread_join()");
    }
    return EXIT_SUCCESS;
}

void  *monThread (void * arg)
{
    long unsigned int n_id;
    for(long unsigned int i=0;i<NBMAX_THREADS;i++){
      if(pthread_equal(pthread_list[i],pthread_self())){
        n_id = i+1;
        for(long unsigned int j=0;j<n_id;j++){
          printf(" ");
        }
        printf("Début du thread nº%ld\n", n_id);
        sleep (rand() % DUREE_MAX + 1);
        for(long unsigned int j=0;j<n_id;j++){
          printf(" ");
        }
        printf("Fin du thread nº%ld\n", n_id);
        break;
      }
    }
    return NULL;
}

void bye (void)
{
    printf("Fin du processus %d\n", getpid());
}
