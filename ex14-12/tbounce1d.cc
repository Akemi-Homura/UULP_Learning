# include <stdio.h>
# include <string.h>
# include <curses.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>

# define MESSAGE "hello"
# define BLANK   "     "

struct arg_set{
    const char* msg;
    int row;
    int col;
    int dir;
    int delay;
};

int main(){
    int ndelay;
    int c;
    pthread_t msg_thread;
    void *moving_msg(void*);

    initscr();
    crmode();
    noecho();
    clear();

    arg_set args;

    args.row = 10;
    args.col = 0;
    args.dir = 1;
    args.delay = 200;
    args.msg = MESSAGE;

    if( pthread_create(&msg_thread, NULL, moving_msg, (void*)&args) ){
        fprintf(stderr,"error creating thread");
        endwin();
        exit(0);
    }

    while(1){
        ndelay = 0;
        c = getch();
        if( c == 'Q' )break;
        if( c == ' ' ) args.dir = -args.dir;
        if( c == 'f' && args.delay > 2 ) ndelay = args.delay / 2;
        if( c == 's' ) ndelay  = args.delay * 2;
        if( ndelay > 0)
            args.delay = ndelay;
    }
    pthread_cancel(msg_thread);
    endwin();
    return 0;
}

void *moving_msg(void* m){
    arg_set *args = (struct arg_set*)m;
    const char* msg = args->msg;

    while(1){
        usleep(args->delay * 1000);
        mvaddstr(args->row,args->col - args->dir,BLANK);
        mvaddstr(args->row,args->col, msg);
        refresh();

        args->col += args->dir;

        if( args->col < 0 && args->dir == -1){
            args->dir = 1;
        }else if( args->col + (int)strlen(msg) >= COLS && args->dir == 1){
            args->dir = -1;
        }
    }
}
