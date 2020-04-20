#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXLEN 80

#define CHECK(sts, msg)				\
	if (-1 == (sts)) {	            \
		perror(msg);				\
		exit(EXIT_FAILURE);			\
	}

int main (void)
{
    int nbLus, nbEcrits;
    char buff [MAXLEN+1];

    CHECK(nbLus = read(0, buff, MAXLEN), "read()");
    CHECK(nbEcrits = write (1, buff, nbLus), "write()");

    return EXIT_SUCCESS;
}
