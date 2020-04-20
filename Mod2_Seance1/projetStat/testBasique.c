#include <stdio.h>
#include <math.h>

#include "stat.h"

#ifndef NBMAX
#define NBMAX 10
#endif 

static double Std(double * t, int n); 
static int testBasique1(void);
static int testBasique2(void);


int testBasique(void)
{ 
    printf("Tests sur un tableau de %d éléments ... ", NBMAX);
    int test1 = testBasique1();
    if (test1 == 0) return testBasique2();
    return test1;
}


static int testBasique1(void)
{
    double table [NBMAX];
    int i;
    double res;
    int taille = sizeof table / sizeof table [0];   
    
    /* Test basique n°1 */
    for (i = 0; i < taille; i++)
        table [i] = 1.;
   
    res = min(table, taille);
    if (res != table[0]) 
    {
        printf("Erreur : min attendu = %f\tmin obtenu = %f\n",
                table[0], res);
        return 1;
    }            
                    
     res = max(table , taille);    
     if (res != table[0])
     {
        printf("Erreur : max attendu = %f\tmax obtenu = %f\n",
                table[0], res);
        return 2;
     }
                
     res = avg(table , taille);    
     if (res != table[0])
     {
        printf("Erreur : moyenne attendue = %f\tmoyenne obtenue = %f\n",
                table[0], res);
        return 3;
     }
                
     res = std(table , taille);    
     if (res != 0)
     {
        printf("Erreur : moyenne attendue = %f\tmoyenne obtenue = %f\n",
                0., res);
        return 4;
     }   
     return 0;
}

static int testBasique2(void)
{
    double table [NBMAX];
    int i;
    double res;
    int taille = sizeof table / sizeof table [0];   
    
    /* Test basique n°2 */
    for (i = 0; i < taille; i++)
        table [i] = i + 1.;
   
    res = min(table, taille);
    if (res != table[0]) 
    {
        printf("Erreur : min attendu = %f\tmin obtenu = %f\n",
                table[0], res);
        return 5;
    }            
                    
     res = max(table , taille);    
     if (res != table[NBMAX - 1])
     {
        printf("Erreur : max attendu = %f\tmax obtenu = %f\n",
                table[NBMAX - 1], res);
        return 6;
     }
                
     res = avg(table , taille);    
     if (res != (NBMAX + 1) / 2.)
     {
        printf("Erreur : moyenne attendue = %f\tmoyenne obtenue = %f\n",
                (table[0] + table[NBMAX - 1]) / 2., res);
        return 7;
     }
                
     res = std(table , taille);    
     if (fabs(res - Std(table, taille)) > 1e-8)
     {
        printf("Erreur : écart-type attendu = %f\técart-type obtenu = %f\n",
                Std(table, taille), res);
        return 8;
     }  
     return 0; 
}


static double Std(double * t, int n)
{
    double S = 0.0;
    double m = avg(t, n);
    int i;
    
    for (i = 0; i < n; i++)
        S += (t[i] - m)* (t[i] - m);
    return sqrt(S / n);
}


