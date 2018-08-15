# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <stdlib.h>
# include "socklib.h"

# define PRONAME "timeclnt"

void talk_with_server(int);

int main(int ac,char** av){
    if(ac != 3){
        fprintf(stderr,"usage: %s ip port\n",PRONAME);
        exit(1);
    }

    int portnum = atoi(av[2]);
    int fd;
    fd = connect_to_server(av[1],portnum);

    if(fd == -1){
        exit(1);
    }
    talk_with_server(fd);
    close(fd);
    return 0;
}

void talk_with_server(int fd){
    char buf[BUFSIZ];
    int n;

    n = read(fd,buf,BUFSIZ);
    write(STDOUT_FILENO,buf,n);
}
