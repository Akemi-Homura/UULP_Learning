# include <stdio.h>
# include <string.h>
# include <curses.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>

# define MAXMSG 10
# define TUNIT  20000

struct propset{
    const char*str;
    int row;
    int delay;
    int dir;
};

pthread_mutex_t mx = PTHREAD_MUTEX_INITIALIZER;

int setup(int,char**,struct propset props[]);

int main(int ac,char** av){
    int             c;
    pthread_t       thrds[MAXMSG];  /* the threads */
    struct propset  props[MAXMSG];  /* properties of string */
    void            *animate(void*);
    int             num_msg;
    int             i;

    if( ac == 1 ){
        printf("usgae: tanimate string..\n");
        exit(1);
    }

    num_msg = setup(ac - 1,av + 1,props);

    /* create all the threads */
    for(int i=0;i<num_msg;i++){
        if( pthread_create(&thrds[i], NULL, animate, (void*)&props[i])){
            fprintf(stderr,"errorr creating thread");
            endwin();
            exit(0);
        }
    }

    /* process user input */
    while(1){
        c = getch();
        if( c == 'Q' || c == 'q')break;
        if( c == ' '){
            for(int i=0;i<num_msg;i++){
                props[i].dir = -props[i].dir;
            }
        }
        if(c >= '0' && c <= '9'){
            i = c - '0';
            if( i < num_msg){
                props[i].dir = -props[i].dir;
            }
        }
        if( c == 's'){
            for(int i=0;i<num_msg;i++){
                props[i].delay *= 2;
            }
        }
        if( c == 'f'){
            for(int i=0;i<num_msg;i++){
                if(props[i].delay > 1){
                    props[i].delay /= 2;
                }
            }
        }
    }

    /* cancel all the threads */
    pthread_mutex_lock(&mx);
    for(int i=0;i<num_msg;i++){
        pthread_cancel(thrds[i]);
    }
    endwin();
    return 0;
}

int setup(int nstrings,char** strings,struct propset props[]){
    int num_msg = ( nstrings > MAXMSG?MAXMSG: nstrings);

    /* assign rows and velocities to each string */
    srand(getpid());
    for(int i=0;i<num_msg;i++){
        props[i].str = strings[i];
        props[i].row = i;
        props[i].delay = 1 + (rand() % 15);
        props[i].dir = ((rand() %2 )?1:-1);
    }

    /* set up curses */
    initscr();
    crmode();
    noecho();
    clear();
    mvprintw(LINES-1,0,"'Q' to quit,'0'..'%d' to bounce",num_msg-1);
    return num_msg;
}

/* the code that runs in each thread */
void *animate(void *arg){
    struct propset *info = (struct propset*)arg;
    int len = strlen(info->str) + 2;
    int col = rand() % (COLS - len - 3);

    while(1){
        usleep(info->delay * TUNIT);

        pthread_mutex_lock(&mx);            /* only one thread */
        mvaddch(info->row,col,' ');         /* can call curses */
        addstr(info->str);                  /* at the same time */
        addch(' ');
        move(LINES-1,COLS-1);
        refresh();
        pthread_mutex_unlock(&mx);

        /* move item to next column and check for bouncing */
        col += info->dir;

        if( col <=0  && info->dir == -1){
            info->dir = 1;
        }else if( col + len >= COLS && info->dir == 1){
            info->dir = -1;
        }
    }
}
