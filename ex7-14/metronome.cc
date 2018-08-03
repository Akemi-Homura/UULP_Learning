# include <stdio.h>
# include "time_util.h"
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>

# define PRONAME "metronome"

void show_usage(const char*);

pid_t *pids;
int pid_num;

int main(int argc,char** argv){
    void send_signals(int);

    if(argc < 3){
        show_usage(PRONAME);
        exit(0);
    }

    int delay = atoi(argv[1]);
    pid_num = argc - 2;
    pids = (int*) malloc(sizeof(int) * pid_num);

    for(int i=2;i<argc;i++){
        pids[i - 2] = atoi(argv[i]);
    }

    signal(SIGALRM,send_signals);
    set_ticker(delay);

    while(1){
        pause();
    }
    return 0;
}

void send_signals(int){
    for(int i=0;i<pid_num;i++){
        kill(pids[i],SIGINT);
    }
}

void show_usage(const char* pro){
    fprintf(stderr,"usage: %s timeitval pid...\n",pro);
}
