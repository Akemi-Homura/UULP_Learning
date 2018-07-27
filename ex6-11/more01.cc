# include <stdio.h>
# include <stdlib.h>
# include "more_util.h"
# include <signal.h>

# define oops(s,x) {perror(s); exit(x);}

void show_header(const char* path);

int main(int argc, char** argv){
    signal(SIGINT,ctrl_c_handler);
    signal(SIGQUIT,ctrl_quit_handler);
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
