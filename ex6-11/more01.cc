# include <stdio.h>
# include <stdlib.h>
# include "more_util.h"
# include <signal.h>

# define oops(s,x) {perror(s); exit(x);}
# define STDIN "/dev/stdin"

void show_header(const char* path);

int main(int argc, char** argv){
    signal(SIGINT,ctrl_c_handler);
    signal(SIGQUIT,ctrl_quit_handler);
    int mode = S_DFL;
    if(argc == 1){
        do_more(mode,STDIN);
    }else{
        char *nxt_name;
        for(int i = 1;i < argc;i++){
            if(i < argc -1){
                mode |= S_MULTI;
                nxt_name = argv[i+1];
            }else{
                nxt_name = NULL;
            }
            do_more(mode,argv[i],nxt_name);
        }
    }
    return 0;
}
