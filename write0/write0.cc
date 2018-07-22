# include <stdio.h>
# include <stdlib.h>
# include "error_process.h"

# define BUFSIZE 1024
# define PRONAME "write0"

void show_usage();

int main(int argc,char** argv){
    if(argc != 2){
        show_usage();
        exit(1);
    }
    FILE* tty;
    if((tty = fopen(argv[1],"w")) == NULL){
        oops("Open tty failed ",argv[1]);
    }

    char buf[BUFSIZE];
    while(fgets(buf,BUFSIZE,stdin) != NULL){
        if(buf[0] == '\0' || buf[0] == EOF){
            break;
        }
        if(fputs(buf,tty) == EOF){
            oops("Puts string failed ",argv[1]);
        }
    }
}

void show_usage(){
    fprintf(stderr,"usaage: %s ttyname\n",PRONAME);
}
