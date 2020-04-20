#include <stdio.h>
#include <string.h>

#define MAXLEN 80
/**
 * char lettre = 'A';
 * printf("%c\n", lettre) --> A
 * printf("%d\n",lettre)--> 65
// char * == char []
/**
 * @param s
 * @return unsigned long int
 */
unsigned long int Strlen(const char s []);
char * Strcpy (char dest [], const char srce[]);
int Strcmp(const char *s, const char *t);

int main(void){
    char s[]="Totoasd";
    char t [MAXLEN + 1];
    int test;
    char *s1 ="hello";
    char s2 [20] ="goodbye";
    int nn= (s1==s2);
    printf("%d\n",s1==s2);
    Strcpy(t, "Toto");
    printf("%s Centrale Lille\n", s);
    //on peut mettre sur la terminal "man strlen"
    //%d decimale 
    printf("t = \"%s\" (longueur = %d) \n", t, Strlen(t));
    //if (s==t) --> sont différents toujours
    if ((test = Strcmp(s,t)) == 0)
        printf("s et t sont égaux\n");
    else
        printf("s et t sont différents (longueur = %d)\n" , Strcmp(s,t));
    return 0;
}

unsigned long int Strlen(const char * s){
    //s[i] == *(s+i)
    //1 option
    /*unsigned long int i;
    for(i = 0;s[i] != '\0'; i++);
    return i;*/
    //2 optiom
    const char *aux;
    for(aux=s; *aux!='\0';aux++);
    return aux-s;
}
//option 1
/*char * Strcpy (char dest [], const char srce[]){
    unsigned int i;
    for(i=0; srce[i] != '\0';i++)
        dest[i] = srce[i];
    dest[i]='\0';
    return dest;
}*/
//option 2
char * Strcpy (char * dest, const char * srce){
    //while(*srce != 0)
   /* while(*srce){
        *dest++=*srce++;*/
       //signification:
        /**dest = *srce;
        dest++;
        srce++;*/
    /*}
    *dest = 0;*/

    while(*dest++=*srce++);
    return dest;
}

int Strcmp(const char *s, const char *t){
    //comme un "while"
    //for(; *s== *t;s++;t++)
    for(; *s != '\0'; s++, t++){
        if( *s!= *t) return *s - *t;
    }
    return *s - *t;
}

void swap(double *x, double *y){
    double aux=*x;
    *x=*y;
    *y=aux;
}