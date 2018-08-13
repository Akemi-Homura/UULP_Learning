# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <strings.h>
# include <sys/types.h>
# include <netinet/in.h>
# include <stdlib.h>
# include <netdb.h>

# define oops(msg) {perror(msg); exit(1);}
# define PORTNUM 15000

# define DEBUG 0
# define RELEASE 1
# define RUNTYPE DEBUG

int main(int ac,char** av){
    struct sockaddr_in servaddr;
    struct hostent  *hp;
    int sock_id;
    char buffer[BUFSIZ];
    int n_read;

    if( ac!=3 )exit(1);

    /** Step 1: Get a socket **/
    sock_id = socket(AF_INET, SOCK_STREAM, 0);
    if( sock_id == -1 ){
        oops("socket");
    }

    /** Step 2: connnet to server **/
    bzero(&servaddr,sizeof(servaddr));
    hp = gethostbyname(av[1]);
    if( hp == NULL ){
        oops(av[1]);
    }
    bcopy(hp->h_addr,(struct sockaddr *)&servaddr.sin_addr,hp->h_length);
    servaddr.sin_port = htons(PORTNUM);
    servaddr.sin_family = AF_INET;

    if( connect(sock_id, (struct sockaddr*)&servaddr, sizeof(servaddr)) != 0){
        oops("connect");
    }

    /** Step 3: send directory name, then read back results **/
    if( write(sock_id, av[2], strlen(av[2])) == -1){
        oops("write");
    }
    if( write(sock_id,"\n",1) == -1){
        oops("write");
    }

    while( (n_read = read(sock_id, buffer, BUFSIZ)) > 0 ){
        if( write(STDOUT_FILENO,buffer,n_read) == -1 ){
            oops("write");
        }
    }
#if RUNTYPE == DEBUG
    printf("n_read = %d\n",n_read);
#endif
    close(sock_id);
    return 0;
}
