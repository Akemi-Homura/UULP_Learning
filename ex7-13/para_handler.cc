# include "para_handler.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# define SHOW_USAGE(pro) {fprintf(stderr,"usage: %s pid [seconds]\n",pro);}
# define PRONAME "timeout"
# define DFLSEC  5
# define PIDINDEX 1
# define SECINDEX 2

void para_handler(int argc,char** argv,pid_t &pid,int &timeout){
    if(argc < 2){
        SHOW_USAGE(PRONAME);
    }
    pid = atoi(argv[PIDINDEX]);
    timeout = DFLSEC;
    if(argc == 3){
        timeout = atoi(argv[SECINDEX]);
    }
}
