# include "socklib.h"
# include <string.h>
# include <stdio.h>
# include <curses.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/socket.h>

# define oops(msg) {perror(msg); exit(1);}

void process_request(int);
void setup();

# define PORTNUM 13000

int main(){
    setup();
    int sock,fd;
    sock = make_server_socket(PORTNUM);
    if( sock == -1){
        endwin();
        oops("make_server_socket");
    }

    while(1){
        fd = accept(sock,NULL,NULL);
        if( fd == -1 ){
            break;
        }
        process_request(fd);
        close(fd);
    }
    return 0;
}

void process_request(int fd){
    char buf[BUFSIZ];
    char msg[100];
    FILE* fp = fdopen(fd,"r");
    while(fgets(buf,BUFSIZ,fp)){
        if(strncmp(buf,"CLEAR",5) == 0){
            clear();
            refresh();
        }else if(strncmp(buf,"DRAW",4) == 0){
            int r,c;
            sscanf(buf+5,"%d%d%[^\n]",&r,&c,msg);
            mvaddstr(r,c,msg);
            move(LINES-1,COLS-1);
            refresh();
        }
    }
}

void setup(){
    initscr();
    crmode();
    noecho();
    clear();
    refresh();
}
