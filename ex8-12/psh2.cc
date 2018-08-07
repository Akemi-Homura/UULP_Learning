# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <curses.h>

# define MAXARGS 20
# define ARGLEN  100
# define BEEP    putchar('\a')

# define RELEASE 0
# define DEBUG   1
# define RUNTYPE DEBUG

# define KEY_DEL 127

# define EXIT(x) {endwin(); exit(x);}

void ctrl_cq_handler(int);
void init_curses();
void execute(char **arglist);
void show_hint();
void get_eof();
void do_shell();

int numargs,row,col;
char argbuf[ARGLEN];

int main(){
    signal(SIGINT,ctrl_cq_handler);
    signal(SIGQUIT,ctrl_cq_handler);
    init_curses();
    do_shell();

    return 0;
}

void get_eof(){
    if(col == 0){
        BEEP;
    }else{
        EXIT(0);
    }
}

void ctrl_cq_handler(int signum){
    if(signum == SIGINT){
        numargs = 0;
        argbuf[0] = '\0';
    }else if(signum == SIGQUIT){
        BEEP;
    }
}

void execute(char **arglist){
    int pid,exitstatus;

    pid = fork();
    switch(pid){
        case -1:
            perror("fork failed");
            EXIT(1);
        case 0:
            execvp(arglist[0],arglist);
            perror("execvp failed");
            EXIT(1);
        default:
            while( wait(&exitstatus) != pid);
            printf("child exited with status %d, %d\n",exitstatus>>8,exitstatus&0377);
    }
}

void show_hint(){
    static char buf[100];

    sprintf(buf,"Arg[%d]? ",numargs);
    mvaddstr(row,0,buf);
    refresh();
    col = strlen(buf);
}

void init_curses(){
    initscr();
    crmode();
    noecho();
    clear();
}

void do_shell(){
    numargs = row = col = 0;

    char *arglist[MAXARGS +1];
    for(int i=0;i<MAXARGS;i++){
        arglist[i] = (char*)malloc(ARGLEN);
    }

    int index = 0;
    while(1){
        show_hint();
        while(1){
            char c = getch();
            if( c == '\n'){
                if(index == 0 && numargs > 0){
                    execute(arglist);
                    numargs =  0;
                }else{
                    ++numargs;
                }
                ++row;
                index = 0;
                break;
            }else if ( c == EOF){
                get_eof();
            }else{
                arglist[numargs][index++] = c;
                mvaddch(row,col++,c);
                refresh();
            }
        }
    }
}
