#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXLEN      80
#define ALPHABSZ    26

#define rot13(phrase)   cesar(phrase, 13)

char * aveCesar (const char * s);
char * dyhCesar (const char * s);
char * cesar(const char * s, int decalage);

void test_aveCesar(void);
void test_dyhCesar(void);
void  test_Cesar(void);


int main (int argc, char * argv [])
{
    test_aveCesar();
    test_dyhCesar();
    test_Cesar();
    
    printf("%s\n", rot13("C'est son fils.")); 
    printf("%s\n", rot13("P'rfg fba svyf."));

    return 0;
}

char * aveCesar (const char * s)
{
    char * res = strdup (s);
    
    for (char *p = res; *p != '\0'; p++)
        if (islower(*p)) 
            *p = (((*p - 'a') + 3) % 26 ) + 'a';
         else if (isupper(*p))
            *p = (((*p - 'A') + 3) % 26 ) + 'A';
         
     return res;
}

char * dyhCesar (const char * s)
{
    char * res = strdup (s);
    
    for (char *p = res; *p != '\0'; p++)
        if (islower(*p)) 
            *p = (((*p - 'a') - 3 + 26) % 26 ) + 'a';
         else if (isupper(*p))
            *p = (((*p - 'A') - 3 + 26) % 26 ) + 'A';
         
     return res;
}


char * cesar(const char * s, int n)
{
    char * res = strdup (s);
    while (n < 0)
        n += ALPHABSZ;
    
    for (char *p = res; *p != '\0'; p++)
        if (islower(*p)) 
            *p = (((*p - 'a') + n) % ALPHABSZ) + 'a';
         else if (isupper(*p))
            *p = (((*p - 'A') + n) % ALPHABSZ) + 'A';
         
     return res;
}


void test_aveCesar(void)
{
    printf("%s\n", aveCesar("ABCDEFGHIJKLMNOPQRSTUVWXYZ"));
    printf("%s\n", aveCesar("TU QUOQUE MI FILI"));
    printf("%s\n", aveCesar("VENI VIDI VICI"));
    printf("%s\n", aveCesar("XIBX GXZQX BPQ"));
    printf("%s\n", aveCesar("PF SFP MXZBJ MXOX YBIIRJ"));
    printf("\n");
}

void test_dyhCesar(void)
{
    printf("%s\n", dyhCesar("DEFGHIJKLMNOPQRSTUVWXYZABC"));
    printf("%s\n", dyhCesar("VDWRU\nDUHSR\nWHQHW\nRSHUD\nURWDV"));
    printf("%s\n", dyhCesar("GHPR GHV PDXA GHV PRWV"));
    printf("%s\n", dyhCesar("YDH YLFWLV"));
    printf("\n");
}

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
