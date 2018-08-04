# include <sys/time.h>
# include <signal.h>
# include <string.h>
# include <curses.h>
# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <limits.h>
# include "time_util.h"

# define TIMES 10
# define MAX_NUM 10
# define DOTLEN 3
# define DELAY 200
# define START_MSG "press s to start game"
# define START_KEY 's'
# define MIN_MSG "    min: "
# define MAX_MSG "    max: "
# define AVA_MSG "average: "

const int flash_index = 6;
const char* blank = " ";

void display_gamestart();
char show_random_number();
long get_ms_time(struct timeval );
void show_result(long min_tm,long max_tm,long ava_tm);
void num_to_str(long v,char *,int);
void ctrl_cq_handler(int);

int row,col,dis_row,dis_col;

int main(){
    initscr();
    crmode();
    noecho();
    clear();
    curs_set(0);

    row = LINES;
    col = COLS;

    signal(SIGINT,ctrl_cq_handler);
    signal(SIGQUIT,ctrl_cq_handler);

    srand(time(NULL));
    display_gamestart();

    struct timeval st_time,ed_time;
    long min_tm = LONG_MAX,max_tm = LONG_MIN,tot_tm = 0,ava_tm;
    for(int i = 0;i < TIMES ; i++ ){
        gettimeofday(&st_time,NULL);
        char res = show_random_number();
        while( getch() != res);
        gettimeofday(&ed_time,NULL);
        long ms_st = get_ms_time(st_time);
        long ms_ed = get_ms_time(ed_time);

        long diff_time = ms_ed - ms_st;
        if(diff_time < min_tm) min_tm = diff_time;
        if(diff_time > max_tm) max_tm = diff_time;
        tot_tm +=diff_time;
    }
    ava_tm = tot_tm / TIMES;

    show_result(min_tm,max_tm,ava_tm);
    char c = '\0';
    while(c!= 'q' && c!='Q'){
        c = getch();
    }
    endwin();
    return 0;
}

void display_gamestart(){
    void on_alarm(int);

    int msg_len = strlen(START_MSG);
    dis_row = row / 2;
    dis_col = (col - msg_len) / 2;

    mvaddstr(dis_row,dis_col,START_MSG);
    refresh();

    signal(SIGALRM,on_alarm);
    set_ticker(DELAY);

    while(getch() != START_KEY);
    clear();
    set_ticker(0);
    signal(SIGALRM,SIG_IGN);
}

void on_alarm(int){
    static bool is_show = false;
    if(is_show){
        mvaddch(dis_row,dis_col + flash_index,START_KEY);
    }else{
        mvaddstr(dis_row,dis_col + flash_index,blank);
    }
    move(LINES-1,0);
    refresh();
    is_show = !is_show;
}

char show_random_number(){
    int dis_col = col / 2;
    int num = rand() % MAX_NUM;
    char c = '0' + num;

    mvaddch(dis_row,dis_col,c);
    move(LINES-1,0);
    return c;
}
long get_ms_time(struct timeval v){
    return v.tv_sec * 1000000 + v.tv_usec;
}

void show_result(long min_tm,long max_tm,long ava_tm){
    int msg_len = strlen(MIN_MSG);
    int dis_col = (col - msg_len - DOTLEN * 2) / 2;
    char numstr[10];
    char disstr[20];

    num_to_str(min_tm,numstr,DOTLEN);
    strcpy(disstr,MIN_MSG);
    strcat(disstr,numstr);
    mvaddstr(dis_row,dis_col,disstr);

    num_to_str(max_tm,numstr,DOTLEN);
    strcpy(disstr,MAX_MSG);
    strcat(disstr,numstr);
    mvaddstr(dis_row + 1,dis_col,disstr);

    num_to_str(ava_tm,numstr,DOTLEN);
    strcpy(disstr,AVA_MSG);
    strcat(disstr,numstr);
    mvaddstr(dis_row + 2,dis_col,disstr);

    move(LINES-1,0);
    refresh();
}

void num_to_str(long v,char *res,int len){
    sprintf(res,"%.*lfs",len,v*1.0 / 1e6);
}

void ctrl_cq_handler(int){
    endwin();
    exit(0);
}
