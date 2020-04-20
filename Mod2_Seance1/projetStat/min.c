#include <stdio.h>

/**
 *  \fn     double min  (double *T, int n)
 *  \brief  Recherche du minimum d'un tableau
 *          de n éléments
 *  \param  T un tableau de réels en double précision
 *  \param  n un entier 
 *  \return la plus petite valeurs parmi les 
 *          n premiers éléments de T
 */
double min  (double *T, int n)
{
    int i, imin = 0 ;
    for (i = 1; i < n; i++)
        if (T[i] < T[imin])
            imin = i;
#if defined(_DEBUG)
    printf("\nMin des %d éléments = %.6f à l'indice %d\n", 
            n, T[imin], imin);
#endif

    return T[imin];
}

