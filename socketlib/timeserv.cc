# include <stdio.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/socket.h>
# include "socklib.h"

# define oops(msg) {perror(msg); exit(1);}

void process_request(int);

# define PORTNUM 13000

int main(){
    int sock,fd;
    sock = make_server_socket(PORTNUM);
    if( sock == -1 ){
        exit(1);
    }

    while(1){
        fd = accept(sock,NULL,NULL);
        if(fd == -1){
            break;
        }
        process_request(fd);
        close(fd);
    }
    return 0;
}

void process_request(int fd){
    int pid = fork();
    switch(pid){
        case -1:
            return;
        case 0:
            dup2(fd,STDOUT_FILENO);
            close(fd);
            execl("/bin/date","date",NULL);
            oops("execlp");
        default:
            wait(NULL);
    }
}
