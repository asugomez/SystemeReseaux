#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "stat.h"
#ifdef _TEST_BASIQUE
#include "testBasique.h"
#endif

#define DEFAUTLSZ   1000

    

double * newRandomTable (int n);

printf
int main(int argc, char *argv[])
{
    double *table_alea;
    int taille = DEFAUTLSZ;
    
#ifdef _TEST_BASIQUE
    int test = testBasique();
    if (test != 0) 
    {
        printf("en échec : code erreur = %d\n", test);
        exit (test);
    }
    printf("OK\n");
 #endif    

    if (argc > 1) taille = atoi(argv[1]);

    table_alea = newRandomTable(taille);

    printf("Min = %.15f\n", min(table_alea, taille));    
    printf("Max = %.15f\n", max(table_alea, taille));    
    printf("Avg = %.15f\n", avg(table_alea, taille));    
    printf("Std = %.15f\n", std(table_alea, taille)); 
    
    free(table_alea);   
    return EXIT_SUCCESS;
}

double * newRandomTable (int n)
{
    double *t;
    int i;
    
    t = (double *)malloc(n * sizeof(double));
    if (t == NULL)
    {
        perror("Espace mémoire disponible, insuffisant");
        exit (EXIT_FAILURE);
    }
    for (i = 0; i < n; i++)
        t [i] = (double)rand() / (RAND_MAX + 1.0);
    return t;
}
