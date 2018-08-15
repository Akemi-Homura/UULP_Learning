# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include "dgram.h"

# define oops(msg,x) {perror(msg); exit(x);}

void say_who_called(struct sockaddr_in*);

int main(int ac,char** av){
    int     port;
    int     sock;
    char    buf[BUFSIZ];
    size_t  msglen;
    struct  sockaddr_in saddr;
    socklen_t saddrlen;

    if( ac == 1 || (port = atoi(av[1])) <= 0){
        fprintf(stderr,"usage: dgrecv portnumber\n");
        exit(1);
    }

    /*
     * get a socket and assign it a port number
     */
    if( (sock = make_dgram_server_socket(port)) == -1 ){
        oops("cannot make socket",2);
    }

    /*
     * receive message on that socket
     */
    saddrlen = sizeof(saddr);
    while((msglen = recvfrom(sock,buf,BUFSIZ,0,(struct sockaddr*)&saddr,&saddrlen))>0){
        buf[msglen] = '\0';
        printf("dgrecv: got a message: %s\n",buf);
        say_who_called(&saddr);
    }
    return 0;
}

void say_who_called(struct sockaddr_in *addrp){
    char host[BUFSIZ];
    int port;

    get_internet_address(host,BUFSIZ,&port,addrp);
    printf("from: %s:%d\n",host,port);
}
