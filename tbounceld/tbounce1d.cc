# include <stdio.h>
# include <string.h>
# include <curses.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>

# define MESSAGE "hello"
# define BLANK   "     "

int row;
int col;
int dir;
int delay;

int main(){
    int ndelay;
    int c;
    pthread_t msg_thread;
    void *moving_msg(void*);

    initscr();
    crmode();
    noecho();
    clear();

    row = 10;
    col = 0;
    dir = 1;
    delay = 200;

    if( pthread_create(&msg_thread, NULL, moving_msg, (void*)MESSAGE) ){
        fprintf(stderr,"error creating thread");
        endwin();
        exit(0);
    }

    while(1){
        ndelay = 0;
        c = getch();
        if( c == 'Q' )break;
        if( c == ' ' ) dir = -dir;
        if( c == 'f' && delay > 2 ) ndelay = delay / 2;
        if( c == 's' ) ndelay  = delay * 2;
        if( ndelay > 0)
            delay = ndelay;
    }
    pthread_cancel(msg_thread);
    endwin();
    return 0;
}

void *moving_msg(void* m){
    const char* msg = (const char*)m;
    while(1){
        usleep(delay * 1000);
        mvaddstr(row,col - dir,BLANK);
        mvaddstr(row,col, msg);
        refresh();

        col += dir;

        if( col < 0 && dir == -1){
            dir = 1;
        }else if( col + (int)strlen(msg) >= COLS && dir == 1){
            dir = -1;
        }
    }
}
