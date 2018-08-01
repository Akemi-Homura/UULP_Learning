# include <stdio.h>
# include <curses.h>
# include <string.h>
# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include "para_util.h"

# define DFLROW 10
# define DFLCOL 20
# define SLPTIME 1

void set_blank(char*,int);
void display(char* msg,int row,int col);

int main(int argc,char** argv){
    void ctrl_cq_handler(int);
    signal(SIGINT, ctrl_cq_handler);
    signal(SIGQUIT, ctrl_cq_handler);

    int len;
    char* msg;
    para_handler(argc,argv,len,msg);

    initscr();
    clear();
    display(msg,DFLROW,DFLCOL);
    return 0;
}

void display(char*msg,int row,int col){
    int len = strlen(msg);
    char *blank = (char*)malloc(len);
    set_blank(blank,len);

    bool flag = true;
    char* display;
    while(1){
        if(flag){
            display = msg;
        }else{
            display = blank;
        }
        flag = !flag;
        mvaddstr(row,col,display);
        move(LINES-1,0);
        refresh();
        sleep(SLPTIME);
    }
}

void set_blank(char* str,int len){
    for(int i=0;i<len;i++){
        str[i] = ' ';
    }
    str[len] = '\0';
}

void ctrl_cq_handler(int){
    endwin();
    exit(0);
}
