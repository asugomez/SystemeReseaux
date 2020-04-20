#include <stdio.h>

double avg  (double *T, int n)
{
    double S = 0;   
    int i;
    for (i = 0; i < n; i++)
        S += T[i];
#if defined(_DEBUG)
    printf("Valeur moyenne des %d éléments = %.6f\n", 
            n, S / n);
#endif   
      return S / n;
}
