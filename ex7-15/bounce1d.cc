# include <stdio.h>
# include <curses.h>
# include <signal.h>
# include <stdlib.h>
# include <string.h>
# include <aio.h>
# include <unistd.h>

# define MESSAGE "hello"
# define BLANK   "     "
# define DELAY 1e6
# define EXIT(x) {endwin();exit(x);}

int row;
int col;
int dir;
int delay;
bool done;

struct aiocb kbcbuf;

int main(){
    void move_msg();
    void on_input(int);
    void setup_aio_buffer();

    initscr();
    crmode();
    noecho();
    clear();

    delay = DELAY;
    row = 10;
    col = 0;
    dir = 1;
    done = false;

    signal(SIGIO,on_input);
    setup_aio_buffer();
    aio_read(&kbcbuf);

    move(row,col);
    addstr(MESSAGE);

    while(!done){
        move_msg();
        usleep(delay);
    }
    endwin();
    return 0;
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

void move_msg(){
    move(row,col);
    addstr( BLANK );
    col += dir;
    move(row,col);
    addstr( MESSAGE );
    refresh();

    if( dir == -1 && col <= 0){
        dir = 1;
    }else if( dir ==1 && col + (int)strlen(MESSAGE) >= COLS){
        dir = -1;
    }
}

void on_input(int){
    int c;
    char *cp = (char*) kbcbuf.aio_buf;

    if(aio_error(&kbcbuf) != 0){
        perror("aio read");
        exit(1);
    }else if(aio_return(&kbcbuf) == 1){
        c = *cp;

        if( c == 'Q' ){ done = true; }
        if( c == ' ' ) dir = -dir;
        if( c == 'f' && delay > 2 ) delay/=2;
        if( c == 's' ) delay*=2;
    }

    aio_read(&kbcbuf);
}
