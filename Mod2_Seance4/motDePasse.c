/**
 * Programme motDePasse.c
 *
 * Le processus motDePasse qui ne peut être interrompu par un contrôle-C,
 * crée un processus fils puis arme une alarme.
 *
 * Le processus fils invite l'utilisateur à entrer un mot de passe dans un
 * délai fixé et avec un nombre de tentatives également limité.
 * Il affiche également un message signalant que le contrôle-C est désactivé
 * lorsque l'utilisateur tape contrôle-C.
 *
 * Le processus fils réalise la lecture et le contrôle du mot de passe
 * saisi par l'utilisateur et signale à son père la raison de sa terminaison :
 *  1)  épuisement des tentatives;
 *  2)  saisie valide du mot de passe.
 *
 * Le processus père affiche un message de dépassement de délai lorsque
 * le temps imparti au processus fils expire ; il
 * arrête alors le processus fils.
 * Il affichera dans le cas contraire, un message signalant
 * que le mot de passe est correct ou non.
 *
 *
 * Compilation : gcc motDePasse.c -o motDePasse -Wall
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

#define TIMEOUT         30
#define NBMAX_ESSAIS    3
#define PASSWORD        "essai"
#define MAXLEN          8

/* ------------------------------------------------------------------------ */
/*                      M A C R O - F O N C T I O N S                       */
/* ------------------------------------------------------------------------ */
#define CHECK(sts, msg)             \
    if (-1 == (sts)) {              \
        perror(msg);                \
        exit(EXIT_FAILURE);         \
    }

/* ------------------------------------------------------------------------ */
/*              P R O T O T Y P E S    D E    F O N C T I O N S             */
/* ------------------------------------------------------------------------ */
static void  signalHandler (int);
void processusFils(int);


/* ------------------------------------------------------------------------ */
/*              V A R I A B L E S    G  L O B A L E S                       */
/* ------------------------------------------------------------------------ */
pid_t   pidFils;


/* ------------------------------------------------------------------------ */
/*              F O N C T I O N    P R I N C I P A L E                      */
/* ------------------------------------------------------------------------ */
int main (int argc, char *argv[])
{
    sigset_t newMask, oldMask;
    struct sigaction newAction;
    int nbEssais = 0;
    int status;
    int pid;
    int timeout = 0;

    /* ------------------------------------------------------------------------ */
    /*  1)  Traitement des arguments de la ligne de commande                    */
    /* ------------------------------------------------------------------------ */
    if (argc > 1)
        timeout = atoi(argv[1]);
    if (timeout <= 0)
        timeout = TIMEOUT;

    if (argc > 2)
        nbEssais = atoi(argv[2]);
    if (nbEssais <= 0)
        nbEssais = NBMAX_ESSAIS;

    /* ------------------------------------------------------------------------ */
    /*  2)  Masquer le Ctrl-C (SIGINT)                                          */
    /* ------------------------------------------------------------------------ */

    /* Initialisation du masque des signaux à ajouter                       */
    CHECK(sigemptyset(&newMask), "sigemptyset()");

    /* Ajout du signal SIGINT                                               */
    CHECK(sigaddset(&newMask, SIGINT), "sigaddset(SIGINT)");
    /* Ajout dans le masque et sauvegarde de l'ancien masque                */
    CHECK(sigprocmask(SIG_BLOCK, &newMask, &oldMask), "sigprocmask()");


    printf("Vous avez %d secondes pour entrer votre mot de passe\n", timeout);

    /* ------------------------------------------------------------------------ */
    /*  3)  Installer le gestionnaire du signal d'alarme                        */
    /*      et le gestion du signal SIGINT pour son fils                        */
    /* ------------------------------------------------------------------------ */
    /* Initialisation de la structure sigaction                                 */
    newAction.sa_handler = signalHandler;
    CHECK(sigemptyset(&newAction.sa_mask), "sigemptyset()");
    newAction.sa_flags = SA_RESTART;
    /* Installation du gestionnaire du signal SIGALRM                           */
    CHECK(sigaction(SIGALRM, &newAction, NULL), "sigaction()");
    /* Installation du gestionnaire du signal SIGINT (pour le fils)             */
    CHECK(sigaction(SIGINT, &newAction, NULL), "sigaction()");

    /* ------------------------------------------------------------------------ */
    /*  4)  Création du processus fils                                          */
    /* ------------------------------------------------------------------------ */
    pidFils = fork();
    switch (pidFils) {
    case -1 :
        perror("Échec de la création d'un processus fils");
        exit (pidFils);

    case 0 :
        processusFils(nbEssais);
        exit (0); /* Fin normale du fils  */

    default :
        /* On met ici la suite du code du processus père */
        printf("Je suis le père du processus ...... n°%d\n", pidFils);
        alarm(timeout);
        break;
    }

    /* ------------------------------------------------------------------------ */
    /*  5)  Attendre la terminaison du fils et analyser la cause de             */
    /*      terminaison.                                                        */
    /* ------------------------------------------------------------------------ */
    CHECK(pid = wait(&status), "wait()");
    printf("\nTerminaison du processus %d\t", pid);

    if (WIFSIGNALED(status))
        switch(WTERMSIG(status)) {
        case SIGUSR2:
            printf("Délai expiré : connexion refusée\n");
            break;
        default:
            fprintf(stderr, "... sur réception du signal %d\n",
                    WTERMSIG(status));
            break;
        }

    else if (WIFEXITED(status))
        switch(WEXITSTATUS(status)) {
        case EXIT_SUCCESS:
            printf("Mot de passe valide : connexion acceptée\n");
            break;
        default:
            printf("Échec des %d tentatives : connexion refusée\n",
                   WEXITSTATUS(status));
            break;
        }
    else
        fprintf(stderr, "Cause d'arrêt ... inconnue\n");

    printf("[%d] Fin du processus père\n", getpid());
    exit(EXIT_SUCCESS);
}

/* --------------------------------------------------------------------------- */
/*              G E S T I O N N A I R E    D E    S I G N A U X                */
/* --------------------------------------------------------------------------- */
static void signalHandler(int numSig)
{
    switch (numSig) {
    case SIGINT:     /*  SIGINT traité par le fils   */
        printf("\t[%d] --> Le Ctrl-c est désactivé.\n",getpid());
        break;

    case SIGALRM:    /*  SIGALRM traité par le père   */
        CHECK(kill(pidFils, SIGUSR2), "kill(USR2)");
        break;

    default:
        printf("Signal %d non traité\n", numSig);
        break;
    }
}

/* --------------------------------------------------------------------------- */
/*      I M P L É M E N T A T I O N   D U   P R O C E S S U S   F I L S        */
/* --------------------------------------------------------------------------- */
void processusFils(int nb)
{
    sigset_t newMask;
    int i;
    char mdp [MAXLEN + 1];
    char *p;

    /* ------------------------------------------------------------------------ */
    /*  1)  Démasquer le signal SIGINT et masquer SIGALRM                       */
    /* ------------------------------------------------------------------------ */
    /* Initialisation du masque des signaux à retirer                           */
    CHECK(sigemptyset(&newMask), "sigemptyset()");

    /* Ajout du signal SIGINT                                                   */
    CHECK(sigaddset(&newMask, SIGINT), "sigaddset(SIGINT)");
    /* Retirer du masque et pas de sauvegarde de l'ancien masque                */
    CHECK(sigprocmask(SIG_UNBLOCK, &newMask, NULL), "sigprocmask(UNBLOCK)");

    /* Initialisation du masque des signaux à ajouter                           */
    CHECK(sigemptyset(&newMask), "sigemptyset()");

    /* Ajout du signal SIGALRM                                                   */
    CHECK(sigaddset(&newMask, SIGALRM), "sigaddset(SIGALRM)");
    /* Retirer du masque et pas de sauvegarde de l'ancien masque                */
    CHECK(sigprocmask(SIG_BLOCK, &newMask, NULL), "sigprocmask(UNBLOCK)");

    printf("Vous avez %d essais pour entrer votre mot de passe, et une "
           "durée limitée\n", nb);

    /* ------------------------------------------------------------------------ */
    /*  2)  Boucle de lecture du mot de passe                                   */
    /* ------------------------------------------------------------------------ */
    for (i = 1; i <= nb; i++) {
        if  (i == 1)
            printf("Premier essai .... : ");
        else if (i == nb)
            printf("Dernier essai .... : ");
        else
            printf("%dème essai ....... : ", i);
        fflush(stdout);

        fgets(mdp, sizeof mdp, stdin);
        if ( (p = strchr(mdp,'\n')) != NULL)
            *p = '\0';
        else
            while (getchar() != '\n');

        if (strcmp(mdp, PASSWORD) == 0)
            exit(EXIT_SUCCESS);
    }

    /* ------------------------------------------------------------------------ */
    /*  3)  Fin avec signalement d'échec                                        */
    /* ------------------------------------------------------------------------ */
    exit(nb);
}

/* ---------------------------------------------------------------------------- */
/* E X E M P L E S  d ' E X É C U T I O N                                       */
/* ---------------------------------------------------------------------------- */
/*

1)  Essai avec 3 échecs successifs
===================================

./motDePasse
Vous avez 30 secondes pour entrer votre mot de passe
Je suis le père du processus ...... n°2565
Vous avez 3 essais pour entrer votre mot de passe, et une durée limitée
Premier essai .... : toto
2ème essai ....... : titi
Dernier essai .... : tata

Terminaison du processus 2565	Échec des 3 tentatives : connexion refusée
[2564] Fin du processus père

2) Essai avec paramètrage de la durée et du nombre d'essais
===========================================================

./motDePasse 5 2
Vous avez 5 secondes pour entrer votre mot de passe
Je suis le père du processus ...... n°2582
Vous avez 2 essais pour entrer votre mot de passe, et une durée limitée
Premier essai .... : titi
Dernier essai .... :
Terminaison du processus 2582	Délai expiré : connexion refusée
[2581] Fin du processus père

3) Essai avec succès
====================

./motDePasse 20 2
Vous avez 20 secondes pour entrer votre mot de passe
Je suis le père du processus ...... n°2589
Vous avez 2 essais pour entrer votre mot de passe, et une durée limitée
Premier essai .... : toto
Dernier essai .... : essai

Terminaison du processus 2589	Mot de passe valide : connexion acceptée
[2588] Fin du processus père

*/
/* --------------------------------------------------------------------------- */

