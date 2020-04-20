#include <stdio.h>
#include <math.h>

#include "avg.h"

double std  (double *T, int n)
{
    double S2 = 0, M = avg(T, n);
    int i;
    
    for (i = 0; i < n; i++)
        S2 += T[i] * T[i];
#if defined(_DEBUG)
    printf("Écart-type des %d éléments = %.6f\n", 
            n, sqrt (S2/n - M*M));
#endif   
  

    return sqrt (S2/n - M*M);
}

