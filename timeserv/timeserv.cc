# include <stdio.h>
# include <arpa/inet.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <netdb.h>
# include <time.h>
# include <string.h>

# define PORTNUM 13000
# define IP      "10.214.59.236"
# define HOSTLEN 256
# define oops(msg)  {perror(msg); exit(1);}

int main(){
    struct sockaddr_in saddr;
    struct hostent *hp;
    char hostname[HOSTLEN];
    int sock_id,sock_fd;
    FILE *sock_fp;
    time_t thetime;

    /*
     * Step 1: ask kernel for a socket
     */
    sock_id = socket(PF_INET, SOCK_STREAM, 0);
    if( sock_id == -1){
        oops("socket");
    }

    /*
     * Step 2: bind address to socket. Address is host,port
     */
    bzero((void*)&saddr, sizeof(saddr));

    gethostname(hostname, HOSTLEN);
    hp = gethostbyname( hostname );

    // memcpy((void*)&saddr.sin_addr, (void*)hp->h_addr,hp->h_length);
    saddr.sin_addr.s_addr = inet_addr(IP);
    saddr.sin_port = htons(PORTNUM);
    saddr.sin_family = AF_INET;

    if(bind(sock_id, (struct sockaddr*)&saddr, sizeof(saddr)) != 0){
        oops( "bind" );
    }

    /*
     * Step 3: allow incoming calls with Qsize=1 on socket
     */
    if( listen(sock_id, 1) != 0 ){
        oops("listen");
    }

    /*
     * main loop: accept(), write(), close()
     */
    while ( 1 ) {
        sock_fd = accept(sock_id, NULL, NULL);
        printf("Wow! got a call!\n");
        if( sock_fd == -1 ){
            oops( "accept" );
        }

        sock_fp = fdopen(sock_fd, "w");
        if( sock_fp == NULL ){
            oops("fdopen");
        }

        thetime = time(NULL);

        fprintf( sock_fp, "The time here is.." );
        fprintf( sock_fp, "%s", ctime(&thetime));
        fclose( sock_fp );
    }
}
