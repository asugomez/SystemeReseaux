#include <unistd.h>
#define MAXLEN 80

int main (void) {
    int nbLus , nbEcrits;
    char buff [MAXLEN+1];
    //read() qui lit des octets depuis un dispositif d’entrée
    nbLus = read(0, buff , MAXLEN);
    //me write() qui écrit des octets sur un dispositif de sortie
    nbEcrits = write (1, buff , nbLus);

    return 0;
}

//gcc appelSys.c -S
//gcc appelSys.c -static -o appelSys
//objdump appelSys -D > appelSys.txt
