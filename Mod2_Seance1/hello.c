#include <stdio.h>

int main(int argc, char * argv[]){
    int i=0;
    int n=5; //iteration
    if(argc>2){
        n=atoi(argv[2]);
    }  
    if (argc > 1){
        for(i=0;i<5;i++){
            if (i%2==0)
                //pour mettre de parenthesis " \"%s\" "
                printf("Hello \"%s\"\t", argv [1]);
            else
                printf("Hello \"%s\"\n", argv [1]);
        }
    }
    else{
        for(i = 0; i<5;i++){
            if (i%2==0)
                printf("Hello World\t");
            else
                printf("Hello World\n");
        }
    }
    return 0;

}