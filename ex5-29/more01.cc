# include <stdio.h>
# include <stdlib.h>
# include "more_util.h"

# define oops(s,x) {perror(s); exit(x);}

int main(int argc, char** argv){
    FILE* fp;
    if(argc == 1){
        do_more(stdin);
    }else{
        while(--argc){
            if((fp = fopen(*++argv,"r")) != NULL){
                do_more(fp);
            }else{
                oops("fopen",1);
            }
        }
    }
    return 0;
}
