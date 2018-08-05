# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>

# define MAXARGS 20
# define ARGLEN  100

void execute(char **arglist);

int main(){
    char *arglist[MAXARGS +1];
    int numargs;
    char argbuf[ARGLEN];

    numargs = 0;
    while( numargs < MAXARGS ){
        printf("Arg[%d]? ",numargs);
        if ( fgets(argbuf,ARGLEN,stdin) && *argbuf != '\n'){
            arglist[numargs++] = strndup(argbuf,strlen(argbuf) -1);
        }else if( numargs > 0 ){
            arglist[numargs] = NULL;
            execute(arglist);
            numargs = 0;
        }
    }
    return 0;
}

void execute(char **arglist){
    int pid,exitstatus;
    
    pid = fork();
    switch(pid){
        case -1:
            perror("fork failed");
            exit(1);
        case 0:
            execvp(arglist[0],arglist);
            perror("execvp failed");
            exit(1);
        default:
            while( wait(&exitstatus) != pid);
            printf("child exited with status %d, %d\n",exitstatus>>8,exitstatus&0377);
    }
}
