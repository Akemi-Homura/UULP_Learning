# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <time.h>

# define PRONUMS 3
# define SLPTIME 5

void child_code(int);
void set_signal_handler();
void child_exit_handler(int);

int pro_nums;

int main(int argc,char** argv){
    int newpid;
    pro_nums = PRONUMS;
    if(argc > 1){
        pro_nums = atoi(argv[1]);
    }

    for(int i=0;i<pro_nums;i++){
        if( (newpid = fork()) == -1){
            perror("fork");
        }else if( newpid == 0){
            child_code(SLPTIME);
        }
    }

    set_signal_handler();

    while(1){
        printf("waiting\n");
        sleep(1);
    }

    return 0;
}

void set_signal_handler(){
    struct sigaction act;
    act.sa_handler = child_exit_handler;
    act.sa_flags   = SA_NODEFER  ;
    sigaction(SIGCHLD,&act,NULL);
}

void child_code(int delay){
    printf("child %d here. will sleep for %d seconds\n",getpid(),delay);
    sleep(delay);
    printf("child done. about to exit\n");
    exit(17);
}

void child_exit_handler(int){
    static int exit_nums = 0;

    int wait_rv = wait(NULL);
    printf("done waiting for %d.\n",wait_rv);

    if( ++exit_nums == pro_nums){
        exit(0);
    }
}
