# include <stdio.h>
# include <sys/wait.h>
# include <errno.h>
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

    void ctrl_c_handler(int);
    signal(SIGINT,ctrl_c_handler);

    while(1){
        fd = accept(sock,NULL,NULL);
        if(fd == -1){
            if(errno == EINTR){
                printf("Interrupted by a singal\n");
                continue;
            }
            break;
        }
        process_request(fd);
        close(fd);
    }
    return 0;
}

void ctrl_c_handler(int){
    printf("Get a SIGINT signal\n");
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
