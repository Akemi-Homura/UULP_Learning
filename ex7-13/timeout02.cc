# include <stdio.h>
# include <unistd.h>
# include <time.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/stat.h>
# include "para_handler.h"
# include "time_util.h"
# include "error_process.h"

# define DELAY 500
# define TTY "/dev/pts/1"

pid_t pid;
int timeout;

int main(int argc,char**argv){
    void kill_process(int);

    para_handler(argc,argv,pid,timeout);
    printf("%d will be killed after %d seconds\n",pid,timeout);

    signal(SIGALRM,kill_process);
    set_ticker(DELAY);

    while(1){
        pause();
    }
    return 0;
}

void kill_process(int){
    struct stat s_buf;
    if(stat(TTY,&s_buf) == -1){
        oops("stat ",TTY);
    }

    time_t now = time(NULL);
    if(now - s_buf.st_mtime > timeout){
        kill(pid,SIGINT);
        set_ticker(0);
        exit(0);
    }
}
