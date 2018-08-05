# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <time.h>

# define PRONUMS 3

void child_code(int);

int main(int argc,char** argv){
    srand(time(NULL));

    int newpid,pro_nums = PRONUMS;
    if(argc > 1){
        pro_nums = atoi(argv[1]);
    }


    for(int i=0;i<pro_nums;i++){
        int delay = rand() % 10 + 1;
        if( (newpid = fork()) == -1){
            perror("fork");
        }else if( newpid == 0){
            child_code(delay);
        }
    }

    for(int i=0;i<pro_nums;i++){
        int wait_rv = wait(NULL);
        printf("done waiting for %d.\n",wait_rv);
    }

    return 0;
}

void child_code(int delay){
    printf("child %d here. will sleep for %d seconds\n",getpid(),delay);
    sleep(delay);
    printf("child done. about to exit\n");
    exit(17);
}

