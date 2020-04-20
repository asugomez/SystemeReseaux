#include <stdio.h>

double max  (double *T, int n)
{
    int i, imax = 0 ;
    for (i = 1; i < n; i++)
        if (T[i] > T[imax])
            imax = i;
#if defined(_DEBUG)
    printf("Max des %d éléments = %.6f à l'indice %d\n", 
            n, T[imax], imax);
#endif   
  
    return T[imax];
}

