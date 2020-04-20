/* ---------------------------------
test1.c
---------------------------------- */
#include <stdio.h>
#include <stdlib.h>
#define	MAX	15

int tata = 11;	      /* Qq variables globales */
const int tutu = 3;
extern char Msg [];

int main (void)
{
  char * s =  "Toto"; /*Qq variables locales */
  int titi = MAX;

  s [tutu] = 'i' ;/* Toto --> Toti */
  Msg[0] = s [tutu];
  printf("Hello %s = %d\n", s, 3 * titi - tata );
  return EXIT_SUCCESS;
}
