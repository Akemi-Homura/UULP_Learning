# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include "dgram.h"

# define oops(m,x) {perror(m); exit(x);}

int main(int ac,char** av){
    int sock;
    char *msg;
    struct sockaddr_in saddr;

    if( ac!=4 ){
        fprintf(stderr,"usage: dgsend host port 'message'\n");
        exit(1);
    }
    msg = av[3];

    /*
     * get a datagram socket
     */
    if ( (sock = make_dgram_client_socket()) == -1 ){
        oops("cannot make socket",2);
    }

    /*
     * combine hostname and portnumber of destination into an address
     */
    make_internet_address(av[1],atoi(av[2]),&saddr);

    /*
     * send a string through the socket to that address
     */
    if(sendto(sock,msg,strlen(msg),0,(struct sockaddr*)&saddr, sizeof(saddr)) == -1){
        oops("sendto failed",3);
    }
    return 0;
}
