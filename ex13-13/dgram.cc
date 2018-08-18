# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <netdb.h>
# include <string.h>
# include "dgram.h"

# define HOSTLEN 256
# define IP "0.0.0.0"

int make_dgram_server_socket(int portnum){
    struct sockaddr_in saddr;
    int    sock_id;

    sock_id = socket(AF_INET, SOCK_DGRAM, 0);
    if( sock_id == -1 ){ return -1; }

    make_internet_address(IP,portnum,&saddr);

    if( bind(sock_id,(struct sockaddr*)&saddr,sizeof(saddr)) !=0 ){
        return -1;
    }
    return sock_id;
}

int make_dgram_client_socket(){
    return socket(AF_INET, SOCK_DGRAM, 0);
}

int make_internet_address(const char* hostname,int port,struct sockaddr_in* addrp){
    struct hostent *hp;

    bzero(addrp,sizeof(struct sockaddr_in));
    hp = gethostbyname(hostname);
    if( hp == NULL ) return -1;
    memcpy(&addrp->sin_addr,hp->h_addr,hp->h_length);
    addrp->sin_port   = htons(port);
    addrp->sin_family = AF_INET;
    return 0;
}

int get_internet_address(char *host,int len,int *portp,struct sockaddr_in *addrp){
    strncpy(host, inet_ntoa(addrp->sin_addr), len);
    *portp = ntohs(addrp->sin_port);
    return 0;
}
