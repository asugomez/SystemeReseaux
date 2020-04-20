/* ------------------------------------------------------------------------ */
/*   Fichier : cesar_2.c                                                    */
/*                                                                          */
/*  Programme de chiffrement/déchiffrement par substitution                 */
/*  mono alphabétique                                                       */
/*                                                                          */
/*  Compilation : gcc cesar_2.c -Wall -o cesar                              */
/*                                                                          */
/*  Exemples d'usage :                                                      */
/*  1)  ./cesar 13  "Les sanglots longs des violons de l'automne            */
/*          Le programme applique un décalage de 13 sur la phrase           */
/*          présente en paramètre;                                          */
/*                                                                         */
/*  2)  ./cesar "Blessent mon coeur d'une langueur monotone                 */
/*          Le décalage par défaut de 3 est appliqué                        */
/*                                                                          */
/*  3)  ./cesar 9                                                           */
/*          Un décalage de 9 s'applique au texte issu de stdin (clavier,    */
/*          fichier en cas de redirection de stdin                          */
/*                                                                          */
/*  4)  /cesar                                                              */
/*          Décalage de 3, appliqué au texte issu de stdin                  */
/*                                                                          */
/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/*      I N C L U S I O N   D E   F I C H I E R S   d ' E N-T Ê T E         */
/* ------------------------------------------------------------------------ */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* ------------------------------------------------------------------------ */
/*             D É F I N I T I O N S   D E   C O N ST A N T E S             */
/* ------------------------------------------------------------------------ */
#define MAXLEN      80
#define ALPHABSZ    26
#define DEF_DECAL   3

/* ------------------------------------------------------------------------ */
/*                      M A C R O - F O N C T I O N S                       */
/* ------------------------------------------------------------------------ */
#define rot13(phrase)   cesar(phrase, 13)

/* ------------------------------------------------------------------------ */
/*              P R O T O T Y P E S   D E   F O N C T I O N S               */
/* ------------------------------------------------------------------------ */

/* ------------------------ Fonctions de base ----------------------------- */
char * aveCesar (const char * s);
char * dyhCesar (const char * s);
char * cesar    (const char * s, int decalage);

/* ------------------------ Fonctions de test ----------------------------- */
void test_aveCesar(void);
void test_dyhCesar(void);
void test_Cesar(void);


int main (int argc, char * argv [])
{
    int n = 0;
    char ligne[MAXLEN + 1] = "";

#if (0)
    test_aveCesar();
    test_dyhCesar();
    test_Cesar();

    printf("%s\n", rot13("P'rfg fba svyf."));
#endif

    switch (argc) {
    case 3 :    // deux argments : <decalage> et <phrase>
        printf("%s\n", cesar(argv[2], atoi(argv[1])));
        return 0;

    case 2 :    // un argument, deux cas : <decalage> OU <phrase>
        n = atoi(argv[1]);
        if (n == 0) {
            printf("%s\n", cesar(argv[1], DEF_DECAL));
            return 0;
        }
        break;

    case 1 :    // pas d'argument
        n = DEF_DECAL;
        break;

    default:
        fprintf(stderr, "Usage : %s [<decalage>] [<phrase>]\n", argv[0]);
        return 1;
    }   /* switch */

    while (fgets(ligne, sizeof(ligne) - 1, stdin) != NULL)
        printf("%s", cesar(ligne, n));

    return 0;
}

/* ------------------------------------------------------------------------ */
char * aveCesar (const char * s)
{
    char * res = strdup (s);
    char *p;
    for (p = res; *p != '\0'; p++)
        if (islower(*p))
            *p = (((*p - 'a') + 3) % 26 ) + 'a';
        else if (isupper(*p))
            *p = (((*p - 'A') + 3) % 26 ) + 'A';
    return res;
}

/* ------------------------------------------------------------------------ */
char * dyhCesar (const char * s)
{
    char * res = strdup (s);
    char *p;
    for (p = res; *p != '\0'; p++)
        if (islower(*p))
            *p = (((*p - 'a') - 3 + 26) % 26 ) + 'a';
        else if (isupper(*p))
            *p = (((*p - 'A') - 3 + 26) % 26 ) + 'A';
    return res;
}


/* ------------------------------------------------------------------------ */
char * cesar(const char * s, int n)
{
    char * res = strdup (s);
    char * p;
    while (n < 0) n += ALPHABSZ;
    for (p = res; *p != '\0'; p++)
        if (islower(*p))
            *p = (((*p - 'a') + n) % ALPHABSZ) + 'a';
        else if (isupper(*p))
            *p = (((*p - 'A') + n) % ALPHABSZ) + 'A';
    return res;
}


/* ------------------------------------------------------------------------ */
void test_aveCesar(void)
{
    printf("%s\n", aveCesar("ABCDEFGHIJKLMNOPQRSTUVWXYZ"));
    printf("%s\n", aveCesar("TU QUOQUE MI FILI"));
    printf("%s\n", aveCesar("VENI VIDI VICI"));
    printf("%s\n", aveCesar("XIBX GXZQX BPQ"));
    printf("%s\n", aveCesar("PF SFP MXZBJ MXOX YBIIRJ"));
    printf("\n");
}

/* ------------------------------------------------------------------------ */
void test_dyhCesar(void)
{
    printf("%s\n", dyhCesar("DEFGHIJKLMNOPQRSTUVWXYZABC"));
    printf("%s\n", dyhCesar("VDWRU\nDUHSR\nWHQHW\nRSHUD\nURWDV"));
    printf("%s\n", dyhCesar("GHPR GHV PDXA GHV PRWV"));
    printf("%s\n", dyhCesar("YDH YLFWLV"));
    printf("\n");
}

/* ------------------------------------------------------------------------ */
void test_Cesar(void)
{
    printf("%s\n", cesar("ABCDEFGHIJKLMNOPQRSTUVWXYZ", 3));
    printf("%s\n", cesar("TU QUOQUE MI FILI", 3));
    printf("%s\n", cesar("VENI VIDI VICI", 3));
    printf("%s\n", cesar("XIBX GXZQX BPQ", 3));
    printf("%s\n", cesar("PF SFP MXZBJ MXOX YBIIRJ", 3));
    printf("\n");

    printf("%s\n", cesar("DEFGHIJKLMNOPQRSTUVWXYZABC", -3));
    printf("%s\n", cesar("VDWRU\nDUHSR\nWHQHW\nRSHUD\nURWDV", -3));
    printf("%s\n", cesar("GHPR GHV PDXA GHV PRWV", -3));
    printf("%s\n", cesar("YDH YLFWLV", -3));
    printf("\n");
}
/* ------------------------------------------------------------------------ */
