#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define ALPHABSZ 26
#define DECAL 3
#define MAXLEN 80

char * aveCesar (const char * s);
void test_aveCesar(void);
char* dyhCesar (const char *s);
void test_dyhCesar(void);
char * Cesar (const char * s, int decal);
void test_Cesar(void);

int main(int argc, char * argv[]){
    int decal = 0;
    char ligne [MAXLEN +1];
    if(argc >2){
        decal=atoi(argv[1]);
        strcpy(ligne, argv[2]);
        printf("En clair ..........: \"%s\"\n", ligne);
        printf("Version chiffre :  \"%s\"\n", Cesar(ligne,decal));
    }
    else if (argc==2){
        decal=atoi(argv[1]);
        if (decal == 0){
            decal= DECAL;
            strcpy(ligne, argv[1]);
            printf("En clair ..........: \"%s\"\n", ligne);
            printf("Version chiffre :  \"%s\"\n", Cesar(ligne,decal));
        }
        else{
            while(fgets(ligne, sizeof(ligne)-1,stdin)!=NULL){
                printf("En clair ..........: \"%s\"\n", ligne);
                printf("Version chiffre :  \"%s\"\n", Cesar(ligne,decal));
            }
        }
    }

    /*test_aveCesar();
    printf("\n");
    test_dyhCesar();
    printf("\n");
    test_Cesar();*/
    return EXIT_SUCCESS; 
}
//codificar
char * aveCesar (const char *s){
    char *aux = strdup(s), *debut;
    for(debut=aux; *aux != '\0'; aux++){
        if(islower(*aux)){
            //resta valor ASCII de la 'a'
            *aux=((*aux - 'a' )+ DECAL) % ALPHABSZ + 'a';
        }
        else if(isupper(*aux)){
            *aux=((*aux - 'A') + DECAL) % ALPHABSZ + 'A';
        }
    }
    return debut;
}
//decodificar
char* dyhCesar (const char *s){
    char *aux = strdup(s), *debut;

    for(debut=aux; *aux != '\0'; aux++){
        if(islower(*aux)){
            //resta valor ASCII de la 'a'
            *aux=((*aux - 'a' )- DECAL ) %ALPHABSZ + 'a';
        }
        else if(isupper(*aux)){
            *aux=((*aux - 'A') - DECAL ) % ALPHABSZ + 'A';
        }
    }
    return debut;
}

//generale
char * Cesar (const char * s, int decal){
    char *aux = strdup(s), *debut;

    for(debut=aux; *aux != '\0'; aux++){
        if(islower(*aux)){
            //resta valor ASCII de la 'a'
            *aux=((*aux - 'a' )+ decal ) %ALPHABSZ + 'a';
        }
        else if(isupper(*aux)){
            *aux=((*aux - 'A') + decal) % ALPHABSZ + 'A';
        }
    }
    return debut;

}

void test_aveCesar(void){
    printf("%s\n", aveCesar("ABCDEFGHIJKLMNOPQRSTUVWXYZ"));
    printf("%s\n", aveCesar("TU QUOQUE MI FILI"));
    printf("%s\n", aveCesar("VENI VIDI VICI"));
    printf("%s\n", aveCesar("XIBX GXZQX BPQ"));
    printf("%s\n", aveCesar("PF SFP MXZBJ MXOX YBIIRJ"));
}

void test_dyhCesar(void){
    printf("%s\n", dyhCesar("DEFGHIJKLMNOPQRSTUVWXYZABC"));
    printf("%s\n", dyhCesar("VDWRU\nDUHSR\nWHQHW\nRSHUD\nURWDV"));
    printf("%s\n", dyhCesar("GHPR GHV PDXA GHV PRWV"));
    printf("%s\n", dyhCesar("YDH YLFWLV"));
}

void test_Cesar(void){
    printf("%s\n", Cesar("ABCDEFGHIJKLMNOPQRSTUVWXYZ",+3));
    printf("%s\n", Cesar("TU QUOQUE MI FILI",+3));
    printf("%s\n", Cesar("VENI VIDI VICI",+3));
    printf("%s\n", Cesar("XIBX GXZQX BPQ",+3));
    printf("%s\n", Cesar("PF SFP MXZBJ MXOX YBIIRJ",+3));
    printf("%s\n", Cesar("DEFGHIJKLMNOPQRSTUVWXYZABC",-3));
    printf("%s\n", Cesar("VDWRU\nDUHSR\nWHQHW\nRSHUD\nURWDV",-3));
    printf("%s\n", Cesar("GHPR GHV PDXA GHV PRWV",-3));
    printf("%s\n", Cesar("YDH YLFWLV",-3));

}