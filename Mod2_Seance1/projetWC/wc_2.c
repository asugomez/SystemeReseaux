/* ------------------------------------------------------------------------ */
/*   Fichier : wc_2.c                                                       */
/*                                                                          */
/* 2nde étape du programme de comptage des caractères, mots et lignes       */
/*                                                                          */
/*                                                                          */
/*      Cette version compte les lignes les mots et les caractères          */
/*                                                                          */
/*  Compilation : gcc wc_2.c -Wall -o wc                                    */
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

    /*  Ajout du compteur de mots                                           */
    unsigned int nbMots = 0;

    int dansMot = 0;    /*
                         * état de l'automate de reconnaissance de mots
                         *   dansMot = 0 --> on n'est pas/plus dans un mot
                         *                   c'est l'état initial
                         *   dansMot = 1 --> on est dans un mot
                         */

    char    carLu;  /* le caractère qui vient d'être lu                     */

    while ( (carLu = getchar() ) != EOF) {
        nbCar++;    /* tous les caractères lus sont comptabilisés           */
        switch (carLu) {
        case '\n' :
            nbLignes++;
        case '\t' :
        case ' '  : /* partie commune au traitement de '\n', '\t', ' '      */
            if (dansMot) {
                dansMot = 0; /* on vient de détecter la fin d'un mot        */
                nbMots++;
            }
            break;
        default :   /* cas des autres caractères                            */
            dansMot = 1;
            break;
        }
    }

    /*
     *  Affichage de la valeur des 3 compteurs.
     *      %d  --> affichage de la valeur d'un int
     *      %u  --> affichage de la valeur d'un unsigned int
     */
    printf("Nombre de caractères ... = %u\n", nbCar);
    printf("Nombre de mots ......... = %u\n", nbMots);
    printf("Nombre de lignes ....... = %u\n", nbLignes);

    return 0;   /* terminaion normale du programme                          */
}