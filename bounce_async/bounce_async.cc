# include <stdio.h>
# include <curses.h>
# include <signal.h>
# include <fcntl.h>
# include <unistd.h>
# include "time_util.h"
# include <string.h>

# define MESSAGE "hello"
# define BLANK   "     "

# define RELEASE 0
# define DEBUG 1
# define RUNTYPE  RELEASE

int row = 10;
int col = 0;
int dir = 1;
int delay = 200;
int done  = 0;

int main(){
    void on_alarm(int);
    void on_input(int);
    void enable_kbd_signals();

    initscr();
    crmode();
    noecho();
    clear();

    signal(SIGIO,on_input);
    enable_kbd_signals();
    signal(SIGALRM,on_alarm);
    set_ticker(delay);

    move(row,col);
    addstr( MESSAGE );

    while(!done) {
#if RUNTYPE == DEBUG
        fprintf(stderr,"done=%d\n",done);
#endif
        pause();
    }

    endwin();
}

void on_input(int){
    signal(SIGIO, SIG_IGN);
    int c = getch();
#if RUNTYPE == DEBUG
    static int row_num = 0,col_num = 0;
    mvaddch(row_num++,col_num++,c);
    refresh();
#endif
    // printf(stderr,"inputing");
    if( c == 'Q' || c ==EOF ){
        done = 1;
    }else if( c == ' '){
        dir = -dir;
    }
    signal(SIGIO,on_input);
}

void on_alarm(int){
    signal(SIGALRM, SIG_IGN);
    mvaddstr(row,col,BLANK);
    col += dir;
    mvaddstr(row, col, MESSAGE);
    refresh();

    if( dir == -1 && col <= 0 ){
        dir = 1;
    }else if ( dir == 1 && col + int(strlen(MESSAGE)) >= COLS){
        dir = -1;
    }
    signal(SIGALRM,on_alarm);
}

void enable_kbd_signals(){
    int fd_flags;

    // int fd = open("/dev/tty",O_RDONLY);

    fcntl(0, F_SETOWN, getpid());
    fd_flags = fcntl(0, F_GETFL);
    fcntl(0, F_SETFL, (fd_flags | O_ASYNC));
}
