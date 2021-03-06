# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>

# define DELAY 5

int main(){
    int newpid;
    void child_code(int),parent_code();

    printf("Before: my pid is %d\n",getpid());

    if( (newpid = fork()) == -1){
        perror("fork");
    }else if( newpid == 0){
        child_code(DELAY);
    }else{
        parent_code();
    }
}

void child_code(int delay){
    printf("child %d here. will sleep for %d seconds\n",getpid(),delay);
    sleep(delay);
    printf("child done. about to exit\n");
    exit(17);
}

void parent_code(){
    void child_exit_handler(int);
    signal(SIGCHLD,child_exit_handler);

    while(1){
        printf("waiting\n");
        sleep(1);
    }
}

void child_exit_handler(int){
    int wait_rv,child_status;

    wait_rv = wait(&child_status);
    printf("done waiting for %d.\n",wait_rv);
    printf("status: exit = %d, sig = %d, core = %d\n",WEXITSTATUS(child_status), WTERMSIG(child_status), WCOREDUMP(child_status));
    exit(0);
}
