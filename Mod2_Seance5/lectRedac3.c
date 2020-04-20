/* ------------------------------------------------------------------------ */
/*                   E N T Ê T E S    S T A N D A R D S                     */
/* ------------------------------------------------------------------------ */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <errno.h>
#include <time.h>
#include <sched.h>

/* ------------------------------------------------------------------------ */
/*              C O N S T A N T E S     S Y M B O L I Q U E S               */
/* ------------------------------------------------------------------------ */
#define NBMAX_BUFFER	3
#define MAX_VALUE	    10
#define OVER            (-1)

#define TEMPO_1ms       100000L
#define MAXLEN          255

#define NBLECTEURS      3   
#define NBREDACTRS      2

/* ------------------------------------------------------------------------ */
/*              D É F I N I T I O N S   D E   T Y P E S                     */
/* ------------------------------------------------------------------------ */
typedef void * (*pf_t) (void *);

typedef struct {              /* buffer circulaire d'entiers                */
    int buffer[NBMAX_BUFFER]; /* la zone de stockage                        */
    sem_t semBufferVide[NBLECTEURS];
    sem_t semBufferPlein[NBLECTEURS];
    int nextValue;          /* next value to writePos */
    int writePos;           /* indice du prochain compartiment à remplis    */
    pthread_mutex_t mutexWrite; 
} circBuffer_t;

/* ------------------------------------------------------------------------ */
/*                      M A C R O - F O N C T I O N S                       */
/* ------------------------------------------------------------------------ */
#define CHECK_T(status, msg)                                                 \
  if (0 != (status))   {                                                     \
    fprintf(stderr, "pthread erreur : %s\n", msg);                           \
    exit (EXIT_FAILURE);                                                     \
  }

#define CHECK(status, msg)                                                   \
    if (-1 == (status)) {                                                    \
        perror(msg);                                                         \
        exit(EXIT_FAILURE);                                                  \
    }

/* ------------------------------------------------------------------------ */
/*                 V A R I A B L E S    G L O B A L E S                     */
/* ------------------------------------------------------------------------ */
circBuffer_t buf;
pthread_mutex_t mutexEcran;
/* ------------------------------------------------------------------------ */
/*            P R O T O T Y P E S    D E    F O N C T I O N S               */
/* ------------------------------------------------------------------------ */
void   redacteur(long noR);
void   lecteur(long noL);
void   init(circBuffer_t * b);
void   tempo(int minDelai, int maxDelai);
void   putLine (const char *s);

/* ------------------------------------------------------------------------ */
int main(int argc, char * argv[])
{
#if !defined(NOREADER)
    pthread_t tidLecteur[NBLECTEURS];
#endif

#if !defined(NOWRITER)
    pthread_t tidRedact[NBREDACTRS];
#endif
    long i;

    printf("Lancement du programme d'id   = 0x%08lx\n",
           (long)pthread_self());

    srand(time(NULL));
    init(&buf);
    CHECK_T(pthread_mutex_init(& mutexEcran, NULL),"pthread_mutex_init()");
        

#if !defined(NOREADER)
    for(i=0;i<NBLECTEURS;i++){
        CHECK_T(pthread_create(&tidLecteur[i], NULL, (pf_t)lecteur, (void *) i),
                "pthread_create(lecteur)");
    }
#endif

#if !defined(NOWRITER)
    for(i=0;i<NBREDACTRS;i++){
        CHECK_T(pthread_create(&tidRedact[i], NULL, (pf_t)redacteur, (void *) i),
                "pthread_create(redacteur)");
    }
#endif

#if !defined(NOREADER)
    for(i=0;i<NBLECTEURS;i++){
        CHECK_T(pthread_join(tidLecteur[i], NULL), "pthread_join(lecteur)");
    }
#endif

#if !defined(NOWRITER)
    for(i=0;i<NBREDACTRS;i++){
        CHECK_T(pthread_join(tidRedact[i], NULL), "pthread_join(redacteur)");
    }
#endif
    CHECK_T(pthread_mutex_destroy(&mutexEcran),"pthread_mutex_destroy()");
    for(i=0;i<NBLECTEURS;i++){
        CHECK(sem_destroy(&buf.semBufferVide[i]), "sem_destroy()");
        CHECK(sem_destroy(&buf.semBufferPlein[i]), "sem_destroy()");
    }
    return 0;
}

/* ------------------------------------------------------------------------ */
void  redacteur(long no)
{
    int i = 0, n=0;
    int j;
    char line[MAXLEN + 1];
    buf.writePos++;
    
    printf("Lancement du rédacteur %ld d'id = 0x%08lx\n",
           no, (long)pthread_self());
    
    while  ( buf.nextValue != OVER && n !=OVER) {
        //CHECK_T(pthread_mutex_init(& buf.mutexWrite, NULL),"pthread_mutex_init()");
        for(j=0;j< NBLECTEURS;j++){
            CHECK(sem_wait(&buf.semBufferVide[j]), "sem_wait()");
        }

        if((n+1)==buf.nextValue){
            n++;
        }
        if((i+1)==buf.writePos){
            i++;
        }
        /*------------------------------*/
        if (n == MAX_VALUE)
            buf.buffer[i] = n = OVER;
    
        else
            buf.buffer[i] = n++;
        /*--------------------------*/
        if(buf.nextValue==MAX_VALUE)
            buf.buffer[buf.writePos]= buf.nextValue= OVER;

        else
            buf.buffer[buf.writePos]=buf.nextValue++;
        /*-------------------------------*/
        sprintf(line,"Le rédacteur n°%ld écrit %d dans le buffer %d\n",
                no, buf.buffer[i], i);

        putLine(line);
        for(j=0;j< NBLECTEURS;j++){
            CHECK(sem_post(&buf.semBufferPlein[j]), "sem_post(Plein)");
        }
        i++;
        buf.writePos++;
        if (i == NBMAX_BUFFER) i = 0;
        if(buf.writePos == NBMAX_BUFFER) buf.writePos=0;
        CHECK_T(pthread_mutex_destroy(&buf.mutexWrite),"pthread_mutex_destroy()");
    }
    
}


/* ------------------------------------------------------------------------ */
void  lecteur(long no)
{   
    int i = 0, n = 0;
    char line[MAXLEN + 1];
    printf("Lancement du lecteur %ld d'id   = 0x%08lx\n",
           no, (long)pthread_self());
    while ( n != OVER ) {
        //tempo(10, 100);
        CHECK(sem_wait(&buf.semBufferPlein[no]), "sem_wait()");
        n = buf.buffer[i];
        sprintf(line,"%*sLe lecteur n°%ld lit %d dans le buffer %d\n",
                5 * (int)(no + 1), "   ", no,   n, i);
        putLine(line);
        CHECK(sem_post(&buf.semBufferVide[no]), "sem_post(Vide)");
        i++;
        if (i == NBMAX_BUFFER) i = 0;
    }
}

/* ------------------------------------------------------------------------ */
void init(circBuffer_t * b)
{
    int i;
    for (i = 0; i < NBMAX_BUFFER; i++)
        b->buffer[i] = OVER;

    for(i=0;i <NBLECTEURS;i++){
        CHECK(sem_init(& (b->semBufferPlein[i]),0,0), "sem_init(BufPlein)");
        CHECK(sem_init(& (b->semBufferVide[i]),0,NBMAX_BUFFER), "sem_init(BufVide)");
    }
    b->nextValue=0;
    b->writePos=0;

}

/* ------------------------------------------------------------------------ */
void tempo(int min, int max)
{

    struct timespec delai = { .tv_sec = 0, .tv_nsec = 0};
    delai.tv_nsec = TEMPO_1ms * (min + rand() % (max - min + 1));
    nanosleep(&delai, NULL);
}

/* ------------------------------------------------------------------------ */
void putLine (const char *s)
{
    CHECK_T(pthread_mutex_lock(&mutexEcran),"pthread_mutex_lock()");
    for ( ; *s ==  ' '; s++) printf("%c", *s);
    fflush(stdout);
    for ( ; *s != '\0'; s++) {
        tempo(0, 100);
        printf("%c", *s);
        fflush(stdout);
    }
    CHECK_T(pthread_mutex_unlock(&mutexEcran),"pthread_mutex_lock()");
}

/* ------------------------------------------------------------------------ */
