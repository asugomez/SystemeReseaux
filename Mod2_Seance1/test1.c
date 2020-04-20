#include <stdio.h>
#include <stdlib.h>

int main(){
    int table [5] = {1};
   
    char c='f';
    c &= ~(1<<5);
    printf("%c", c);
}