# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>

# define MAXARGS 20
# define ARGLEN  100

# define EXITMSG "exit"

# define DEBUG   0
# define RELEASE 1
# define RUNTYPE DEBUG

# define BEEP putchar('\a')
# define MAX(a,b) (a>b?a:b)
# define MIN(a,b) (a<b?a:b)

void execute(char **arglist);
void ctrl_c_handler(int);
void init();

int numargs;
bool reprint_prmpt;
struct sigaction act_c ,act_q;

int main(){
    char *arglist[MAXARGS +1];
    char argbuf[ARGLEN];

    init();

    while( numargs < MAXARGS ){
        if(reprint_prmpt){
            printf("Arg[%d]? ",numargs);
        }
        reprint_prmpt = true;
        memset(argbuf,'\0',ARGLEN);
        if ( fgets(argbuf,ARGLEN,stdin) && *argbuf != '\n'){
            arglist[numargs++] = strndup(argbuf,strlen(argbuf) -1);
            if(strcmp(arglist[MAX(0,numargs-1)],EXITMSG) == 0){
                putchar('\n');
                exit(0);
            }
        }else if(feof(stdin)){
            putchar('\n');
            exit(0);
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
            // printf("child exited with status %d, %d\n",exitstatus>>8,exitstatus&0377);
    }
}

void init(){
    numargs       = 0;
    reprint_prmpt = true;

    act_c.sa_handler = ctrl_c_handler;
    act_q.sa_handler = ctrl_c_handler;

    sigaction(SIGINT,&act_c,NULL);
    sigaction(SIGQUIT,&act_q,NULL);
}

void ctrl_c_handler(int){
    numargs = 0;
    putchar('\n');
}
