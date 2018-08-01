# include <stdio.h>
# include <curses.h>
# include <string.h>
# include <unistd.h>
# include <signal.h>
# include <stdlib.h>

# define DFLROW 10
# define DFLCOL 20
# define SLPTIME 1
# define MESSAGE "hello world"

int main(int argc,char** argv){
    void ctrl_cq_handler(int);
    signal(SIGINT, ctrl_cq_handler);
    signal(SIGQUIT, ctrl_cq_handler);

    char *msg = strdup(MESSAGE);
    int len = strlen(msg);
    if(argc > 1){
        len = argc - 2;
        for(int i=0;i<argc;i++){
            len += strlen(argv[0]);
        }
        msg = (char*)malloc(len);

        for(int i=1,tot_len = 0;i<argc;i++){
            strcat(msg,argv[i]);
            int temp_len = strlen(argv[i]);
            msg[tot_len + temp_len ] = ' ';
            tot_len += temp_len + 1;
        }
    }
    char *blank = (char*)malloc(len);
    for(int i=0;i<len;i++){
        blank[i] = ' ';
    }

    initscr();
    clear();
    bool flag = true;
    char* display;
    while(1){
        if(flag){
            display = msg;
        }else{
            display = blank;
        }
        flag = !flag;
        mvaddstr(DFLROW,DFLCOL,display);
        move(LINES-1,0);
        refresh();
        sleep(SLPTIME);
    }
    return 0;
}

void ctrl_cq_handler(int){
    endwin();
    exit(0);
}
