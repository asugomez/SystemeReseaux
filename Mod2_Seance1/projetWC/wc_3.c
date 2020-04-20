/* ------------------------------------------------------------------------ */
/*   Fichier : wc_3.c                                                       */
/*                                                                          */
/* 3e étape du programme de comptage des caractères, mots et lignes         */
/*                                                                          */
/*                                                                          */
/*      Cette version compte les lignes les mots, les caractères ainsi      */
/*      que les caractères alphabétiques sans distinction de casse          */
/*                                                                          */
/*  Compilation : gcc wc_3.c -Wall -std=c99 -o wc                           */
/*  l'option -std=c99 imposée par la déclaration de l'indice de boucle      */
/*  dans la structure for en fin de programme (dans l'affichage)            */
/* ------------------------------------------------------------------------ */

#include <stdio.h>

/*  Taille de l'alphabet = nombre de caractères dans l'alphabet latin 
 *  (pas de caractères accentués ni de c-cédille)
 * 
 *  JAMAIS de = entre le nom symbolique et sa définition !
 *  PAS de point-virgule au bout de la définition !
 */ 

#define ALPHABSZ    26

int main (void)
{
    /*
     *  Déclaration et initialisation des variables de comptage des
     *  lignes et des caractères.
     *  Ces compteurs ne prennent que des valeurs >= 0 --> unsigned int
     */
    unsigned int nbCar = 0;
    unsigned int nbLignes = 0;

    /*  Déclaration et initialisation du compteur de mots                   */
    unsigned int nbMots = 0;
    
    /*  Déclaration d'un tableau de compteurs de caractères alphabétiques 
     *  et initialisation à 0 de toutes ses composantes.
     *
     * !!! unsigned int nbAlpha [ ALPHABSZ ] = { 1, 2, 3 }; permet
     * d'initialiser les 3 premières composantes avec les valeurs
     * indiquées, et toutes les suivantes sont initialisées à 0 !!!
     */   
    unsigned int nbAlpha [ ALPHABSZ ] = { 0 };

    unsigned int nbCarAlpha = 0;    /* compteur de car. alphabétiques       */
    
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
            if (carLu >= 'a' && carLu <= 'z') {
                nbCarAlpha++;
                nbAlpha [ carLu - 'a' ]++;
            }
            else if (carLu >= 'A' && carLu <= 'Z') {
                nbCarAlpha++;
                nbAlpha [ carLu - 'A' ]++;
            }   
            break;
        }
    }

    /*
     *  Affichage de la valeur des 4 compteurs.
     *      %d  --> affichage de la valeur d'un int
     *      %u  --> affichage de la valeur d'un unsigned int
     */
    printf("Nombre de caractères ................. = %u\n",   nbCar);
    printf("Nombre de caractères alphabétiques ... = %u\n",   nbCarAlpha);
    printf("Nombre de mots ....................... = %u\n",   nbMots);
    printf("Nombre de lignes ..................... = %u\n\n", nbLignes);
  
    printf("+=========+============+==============+\n");
    printf("| Lettre  |   Nombre   |  Fréquence   |\n");
    printf("+=========+============+==============+\n");
    
    /*
     * format %6.3f : affichage d'un nombre flottant sur une
     * zone d'affichage de 6 caractères au total, dont un pour
     * le point décimal et 3 pour les chiffres derrière ce point
     * décimal.
     * 
     * %% pour aficher le caractère %
     * 
     * !!! il faut absolument écrire 100.0 (ou 100.) pour forcer
     * le calcul sur des nombres flottants. Si on écrit 100 
     * (l'entier 100) tous les calculs se font sur des entiers
     * y compris la division.
     */

    for (int i = 0; i < ALPHABSZ; i++)
    {
        printf("|     %c   |  %6d    |   %6.3f %%   |\n", 
               i +'a', nbAlpha[i], 100.0 * nbAlpha[i] / nbCarAlpha);
        printf("+---------+------------+--------------+\n");
    }
    printf("\n");    
    return 0;   /* terminaion normale du programme                          */
}