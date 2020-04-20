/* ------------------------------------------------------------------------ */
/*   Fichier : wc_1.c    
/*  ./program < testfile                                                   */
/*                                                                          */
/* 1ère étape du programme de comptage des caractères, mots et lignes       */
/*                                                                          */
/*                                                                          */
/*      Cette version ne compte que les lignes et les caractères            */
/*                                                                          */
/*  Compilation : gcc wc_1.c -Wall -o wc                                    */
/* ------------------------------------------------------------------------ */

#include <stdio.h>

int main (void)
{
    /*
     *  Déclaration et initialisation des variables de comptage des
     *  lignes et des caractères.
     *  Ces compteurs ne prennent que des valeurs >= 0 --> unsigned int
     */
    unsigned int nbCar = 0;
    unsigned int nbLignes = 0;

    char    carLu;  /* le caractère qui vient d'être lu                     */

    while ( (carLu = getchar() ) != EOF) {
        nbCar++;    /* tous les caractères lus sont comptabilisés           */
        if ( carLu == '\n') /* une ligne se termine par un '\n'             */
            nbLignes++;
    }

    /*
     *  Affichage de la valeur de 2 compteurs.
     *      %d  --> affichage de la valeur d'un int
     *      %u  --> affichage de la valeur d'un unsigned int
     */
    printf("Nombre de caractères ... = %u\n", nbCar);
    printf("Nombre de lignes ....... = %u\n", nbLignes);

    return 0;   /* terminaion normale du programme                          */
}