# include <stdio.h>
# include <string.h>
# include <curses.h>
# include "socklib.h"
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>

# define MAXMSG 10
# define TUNIT  20000
# define BUFFERSZ 100

# define IP "45.40.251.253"
# define PORT 13000

# define oops(msg) {perror(msg); exit(1);}

struct propset{
    const char*str;
    int row;
    int delay;
    int dir;
};

struct arg_set{
    const char* str;
    int row;
    int col;
};

pthread_mutex_t mx = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t emptymx = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t fullmx = PTHREAD_MUTEX_INITIALIZER;
int Empty,Full,in,out,fd;
struct arg_set buffer[BUFFERSZ];

int setup(int,char**,struct propset props[]);
struct arg_set produce(int,int,const char*);
void P(int&,pthread_mutex_t&);
void V(int&,pthread_mutex_t&);

int main(int ac,char** av){
    int             c;
    pthread_t       thrds[MAXMSG];  /* the Producer threads */
    pthread_t       cus;            /* the cusumer thread */
    struct propset  props[MAXMSG];  /* properties of string */
    void            *animate(void*);
    void            *display(void*);
    int             num_msg;
    int             i;

    if( ac == 1 ){
        printf("usgae: tanimate string..\n");
        exit(1);
    }

    num_msg = setup(ac - 1,av + 1,props);

    /* create Producer threads */
    for(int i=0;i<num_msg;i++){
        if( pthread_create(&thrds[i], NULL, animate, (void*)&props[i])){
            fprintf(stderr,"errorr creating thread");
            endwin();
            exit(0);
        }
    }

    /* create Cunsumer thread */
    if( pthread_create(&cus,NULL,display,NULL)){
            fprintf(stderr,"errorr creating thread");
            endwin();
            exit(0);
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
    Empty = BUFFERSZ;
    Full  = 0;
    in = out = 0;
    int num_msg = ( nstrings > MAXMSG?MAXMSG: nstrings);

    /* assign rows and velocities to each string */
    srand(getpid());
    for(int i=0;i<num_msg;i++){
        props[i].str = strings[i];
        props[i].row = i;
        props[i].delay = 1 + (rand() % 15);
        props[i].dir = ((rand() %2 )?1:-1);
    }

    fd = connect_to_server(IP,PORT);
    if( fd == -1 ){
        oops("connect_to_server");
        endwin();
        exit(1);
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
    char msgbuf[BUFSIZ];
    sprintf(msgbuf," %s ",info->str);

    while(1){
        usleep(info->delay * TUNIT);
        /* produce */
        struct arg_set p = produce(info->row,col,msgbuf);

        /* put product in buffer */
        P(Empty,emptymx);
        pthread_mutex_lock(&mx);
        buffer[in++] = p;
        in %= BUFFERSZ;
        pthread_mutex_unlock(&mx);
        V(Full,fullmx);

        /* move item to next column and check for bouncing */
        col += info->dir;

        if( col <=0  && info->dir == -1){
            info->dir = 1;
        }else if( col + len >= COLS && info->dir == 1){
            info->dir = -1;
        }
    }
}

void *display(void*){
    FILE* fp = fdopen(fd,"w");
    while(1){
        P(Full,fullmx);
        pthread_mutex_lock(&mx);
        /* get product */
        struct arg_set info = buffer[out++];
        out %= BUFFERSZ;
        pthread_mutex_unlock(&mx);
        V(Empty,emptymx);

        /* process */
        mvaddstr(info.row,info.col,info.str);
        move(LINES-1,COLS-1);
        refresh();

        /* send to server */
        if(fprintf(fp,"DRAW %d %d %s\n",info.row,info.col,info.str) <= 0){
            endwin();
            oops("fprintf");
        }
        fflush(fp);
    }
}

void P(int& S,pthread_mutex_t& M){
    while(S <= 0);
    pthread_mutex_lock(&M);
    S--;
    pthread_mutex_unlock(&M);
}

void V(int& S,pthread_mutex_t& M){
    pthread_mutex_lock(&M);
    S++;
    pthread_mutex_unlock(&M);
}

struct arg_set produce(int row,int col,const char* msg){
    struct arg_set args;
    args.row = row;
    args.col = col;
    args.str = msg;
    return args;
}
