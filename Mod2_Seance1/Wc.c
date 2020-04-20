#include <stdio.h>

#define NBMAX_CAR 26
int main(void){
    char carLu;
    int nbCar = 0;
    int nbLigne = 0;
    int nbMot= 0;
    int dansMot=0;
    int nbAlpha [NBMAX_CAR] = {0};
    while((carLu = getchar()) != EOF){
        nbCar++;

        switch (carLu) {
            case '\n':
                nbLigne ++;

            case '\t':

            case ' ':
                dansMot = 0;
                break;
            default:
                if(dansMot==0)
                    nbMot++;
                if (carLu >= 'a' && carLu <= 'z')
                    nbAlpha [carLu - 'a' ] ++;
                else if (carLu >= 'A' && carLu <= 'Z')
                    nbAlpha [carLu - 'A' ] ++;


                dansMot=1;
                break;

        }
    }
    printf("Nombre de caractères = %d (en octal = 0%o, en hexa = 0x%x)\n",
            nbCar, nbCar, nbCar);
    printf("Nombre de mots = %d\n",
            nbMot);
    printf("Nombre de lignes = %d\n",
            nbLigne);

    for(int i = 0; i< NBMAX_CAR; i++){
        printf("Nombre de '%c' = %3d\n", i + 'a' , nbAlpha[i]);
    }
    return 0;
}