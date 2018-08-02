# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include <sys/types.h>
# include "para_handler.h"

int main(int argc,char**argv){
    void set_killer(pid_t pid,int timeout);

    pid_t pid;
    int timeout;

    para_handler(argc,argv,pid,timeout);
    set_killer(pid,timeout);
    return 0;
}

void set_killer(pid_t pid,int timeout){
    printf("%d will be killed after %d seconds\n",pid,timeout);
    sleep(timeout);
    kill(pid,SIGINT);
}
