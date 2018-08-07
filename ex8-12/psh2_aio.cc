# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <curses.h>
# include <aio.h>
# include <unistd.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>

# define MAXARGS 20
# define ARGLEN  100
# define BEEP    putchar('\a')

# define EXIT(x) { exit(x);}

# define RELEASE 0
# define DEBUG   1
# define RUNTYPE DEBUG

# define KEY_DEL 127
# define KEY_CD  4
# define AIO_SIG SIGIO


void ctrl_cq_handler(int);
void setup_aio_buffer();
void execute(char **arglist);
void get_eof(int index);
void do_shell(int);
void show_hint(int);

struct aiocb kbcbuf;
int numargs,child_pid;

int main(){

    signal(SIGINT,ctrl_cq_handler);
    signal(SIGQUIT,ctrl_cq_handler);

    child_pid = -1;

    show_hint((numargs = 0));
    setup_aio_buffer();
    aio_read(&kbcbuf);

    signal(AIO_SIG,do_shell);

    while(1){
        pause();
    }

    return 0;
}

void get_eof(int index){
#if RUNTYPE == DEBUG
    printf("index=%d\n",index);
#endif
    if(index != 0){
        BEEP;
    }else{
        EXIT(0);
    }
}

void ctrl_cq_handler(int signum){
    if(child_pid != -1){
        // kill(child_pid,signum);
    }
    if(signum == SIGINT){
        numargs = 0;
    }else if(signum == SIGQUIT){
        BEEP;
    }
}


void execute(char **arglist){
    // static char buf[100];
    int pid,exitstatus;

    child_pid = pid = fork();

    switch(pid){
        case -1:
            perror("fork failed");
            EXIT(1);
        case 0:
#if RUNTYPE == DEBUG
            printf("Before execute\n");
#endif
            execvp(arglist[0],arglist);
#if RUNTYPE == DEBUG
            printf("After execute\n");
#endif
            perror("execvp failed");
            EXIT(1);
        default:
            while( wait(&exitstatus) != pid);
            child_pid = -1;
            // sprintf(buf,"child exited with status %d, %d\n",exitstatus>>8,exitstatus&0377);
            // mvaddstr(row,0,buf);
            // refresh();
    }
}

void setup_aio_buffer(){
    static char input[1];
    kbcbuf.aio_nbytes = 1;
    kbcbuf.aio_fildes = STDIN_FILENO;
    kbcbuf.aio_offset = 0;
    kbcbuf.aio_buf    = input;

    kbcbuf.aio_sigevent.sigev_notify = SIGEV_SIGNAL;
    kbcbuf.aio_sigevent.sigev_signo  = SIGIO;
}

void do_shell(int){
    static char *arglist[MAXARGS +1];
    static bool flag = false;
    static int index = 0;

    int c;
    char* cp = (char*) kbcbuf.aio_buf;

    if(!flag){
        for(int i=0;i<MAXARGS + 1;i++){
            arglist[i] = (char*)malloc(ARGLEN);
            memset(arglist[i],0,ARGLEN);
        }
        flag = true;
    }

    if(aio_error(&kbcbuf) != 0){
        perror("reading failed");
    }else if( aio_return(&kbcbuf) == 1){
        c = *cp;
        if( c == EOF || c == KEY_CD){
            get_eof(index);
        }else if ( c == '\n' ){
            if(index == 0){
                if(numargs > 0){
                    arglist[numargs] = NULL;
                    execute(arglist);
                    numargs = 0;
                }
            }else{
                ++numargs;
            }
            show_hint(numargs);
            index = 0;
        }else{
            arglist[numargs][index++] = c;
        }
    }

    aio_read(&kbcbuf);
}

void show_hint(int num){
    printf("Args[%d]? ",num);
    fflush(stdout);
}
