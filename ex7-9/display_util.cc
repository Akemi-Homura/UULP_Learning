# include "display_util.h"
# include <curses.h>
# include <stdio.h>
# include <signal.h>
# include <ctype.h>
# include "error_process.h"
# include "time_util.h"
# include <unistd.h>
# include <aio.h>
# include <fcntl.h>
# include <string.h>

void on_alarm(int);
void on_input(int);
void setup_aio_buffer(const char*);
void show_letter(char);
void cal_rc(int row,int col,int index,int &rIndex,int &cIndex);
void read_complete();

# define BUFSIZE 512
# define BLANK ' '

# define RELEASE 0
# define DEBUG   1
# define RUNTYPE RELEASE

# define EXIT(x) {endwin(); exit(x);}

struct aiocb kbcbuf;
int row,col,delay,unit_len,dis_index,totlen;
bool input_complete;
char* msg;

void display(const char* filepath,int _row,int _col,int speed){
#if RUNTYPE == DEBUG
    printf("filepath: %s\nrow: %d\ncol: %d\nspeed: %d\n",filepath,_row,_col,speed);
#endif
    row             = _row;
    col             = _col;
    input_complete  = false;
    delay           = 1000 / speed;

    initscr();
    crmode();
    noecho();
    clear();

    signal(SIGIO,on_input);
    setup_aio_buffer(filepath);
#if RUNTYPE == DEBUG
    fprintf(stderr,"setup %s complete\n",filepath);
#endif
    aio_read(&kbcbuf);

    signal(SIGALRM,on_alarm);
    set_ticker(delay);

    while(1){
        // pause();
        char c = getch();
        if(isalpha(c)){
            c = tolower(c);
            if( c == 'q' ){ EXIT(0); }
            else if( c == 's' ) set_ticker( (delay = 1000 / --speed) );
            else if( c == 'f' ) set_ticker( (delay = 1000 / ++speed) );
        }
    }
}

void setup_aio_buffer(const char* filepath){
    int fd = open(filepath,O_RDONLY);
    if(fd == -1){
        oops("open error",filepath);
    }

    static char input[BUFSIZE];
    kbcbuf.aio_fildes = fd;
    kbcbuf.aio_nbytes = BUFSIZE;
    kbcbuf.aio_offset = 0;
    kbcbuf.aio_buf    = input;

    kbcbuf.aio_sigevent.sigev_notify = SIGEV_SIGNAL;
    kbcbuf.aio_sigevent.sigev_signo  = SIGIO;
}

void on_input(int){
    signal(SIGIO,SIG_IGN);
    if(aio_error(&kbcbuf) == -1){
        perror("aio reading failed");
        EXIT(0);
    }else if(aio_error(&kbcbuf) == 0){
        unit_len = aio_return(&kbcbuf);
        if(unit_len == 0){
            read_complete();
            return;
        }
        totlen += unit_len;
        kbcbuf.aio_offset = totlen;
        input_complete = true;
        msg = (char*)kbcbuf.aio_buf;
    }
    signal(SIGIO,on_input);
}

void read_complete(){
    signal(SIGALRM,SIG_IGN);
    set_ticker(0);
    move(LINES-1,0);
    refresh();
}

void on_alarm(int){
    signal(SIGALRM,SIG_IGN);
    while(!input_complete);
    show_letter(msg[dis_index]);
    if(++dis_index == unit_len){
        dis_index = 0;
        aio_read(&kbcbuf);
        input_complete = false;
    }
    signal(SIGALRM,on_alarm);
}

void show_letter(char c){
    void update_rc_index(int&,int&,char);
    static int nRIndex,nCIndex;
    // static int pRIndex,pCIndex;

    // mvaddch(pRIndex,pCIndex,BLANK);
    mvaddch(nRIndex,nCIndex,c);
    refresh();

    // pRIndex = nRIndex;
    // pCIndex = nCIndex;

    update_rc_index(nRIndex,nCIndex,c);
}

void update_rc_index(int& rIndex,int& cIndex,char c){
    if(c == '\n' || ++cIndex == col){
        if(++rIndex == row){
            rIndex = 0;
            clear();
        }
        cIndex = 0;
    }
}

