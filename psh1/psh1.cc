# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <string.h>
# include <unistd.h>

# define MAXARGS 20
# define ARGLEN  100

# define RELEASE 0
# define DEBUG   1
# define RUNTYPE RELEASE

void execute(char** arglist);

int main(){
    char* arglist[MAXARGS +1];
    int numargs = 0;
    char argbuf[ARGLEN];

    while( numargs < MAXARGS ){
        printf("Arg[%d]? ",numargs);
        if(fgets(argbuf,ARGLEN,stdin) && *argbuf != '\n'){
            arglist[numargs++] = strndup(argbuf,strlen(argbuf) -1 );
        }else{
            if( numargs > 0 ){
                arglist[numargs] = NULL;
#if RUNTYPE == DEBUG
                for(int i=0;i<numargs;i++){
                    printf("%s ",arglist[i]);
                }
#endif
                execute( arglist );
                numargs = 0;
            }
        }
    }
    return 0;
}

void execute(char **arglist){
    execvp(arglist[0],arglist);
    perror("execp failed");
    exit(1);
}
