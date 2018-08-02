# include <stdio.h>
# include <curses.h>
# include <string.h>
# include <unistd.h>
# include "screensz.h"
# include <math.h>

# define TIMES 1e6
# define PI M_PI

useconds_t cal_slp_time(int col,int x);

int main(){
    const char* message = "o";
    const char* blank   = " ";
    int dir             = +1;
    int pos             = 0;
    int leftedge        = 0;
    int rightedge,row;

    get_winsize(row,rightedge);

    row >>= 1;
    rightedge -= strlen(message);

    initscr();
    clear();

    while(1){
        move(row,pos);
        addstr(message);
        move(LINES-1,COLS-1);
        refresh();
        usleep(cal_slp_time(rightedge,pos));
        move(row,pos);
        addstr(blank);
        pos += dir;
        if(pos >= rightedge){
            dir = -1;
        }
        if(pos <= leftedge){
            dir = +1;
        }
    }
}

useconds_t cal_slp_time(int col,int x){
    return ( 1.2 - sin(x*PI/col))  * TIMES;
}
