# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <strings.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <netdb.h>

# define oops(msg) {perror(msg); exit(1);}

int main(int ,char** av){
    struct sockaddr_in servadd;
    struct hostent *hp;
    int sock_id;
    char message[BUFSIZ];
    int messlen;

    /*
     * Step 1: Get a socket
     */
    sock_id = socket(AF_INET, SOCK_STREAM, 0);
    if( sock_id == -1 ){
        oops( "socket" );
    }

    /*
     * Step 2: connet to server
     *  need to build address(host,port) of server first
     */
    bzero(&servadd,sizeof(servadd));

    hp = gethostbyname(av[1]);
    if(hp == NULL){
        oops(av[1]);
    }

    bcopy(hp->h_addr,(struct sockaddr *)&servadd.sin_addr,hp->h_length);
    servadd.sin_port = htons(atoi(av[2]));
    servadd.sin_family = AF_INET;

    if(connect(sock_id, (struct sockaddr*)&servadd,sizeof(servadd))!=0){
        oops("connect");
    }

    /*
     * Step 3: transfer data from server, then hangup
     */
    messlen = read(sock_id, message, BUFSIZ);
    if(messlen == -1){
        oops("read");
    }
    if(write(1,message,messlen) != messlen){
        oops("write");
    }
    close(sock_id);
    return 0;
}
