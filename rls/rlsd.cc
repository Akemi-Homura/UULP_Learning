# include <stdio.h>
# include <arpa/inet.h>
# include <string.h>
# include <ctype.h>
# include <sys/socket.h>
# include <strings.h>
# include <unistd.h>
# include <stdlib.h>
# include <netinet/in.h>
# include <netdb.h>
# include <time.h>

# define PORTNUM 15000
# define HOSTLEN 256
# define ADDRESS "0.0.0.0"
# define oops(msg) {perror(msg); exit(1);}

# define DEBUG 0
# define RELEASE 1
# define RUNTYPE RELEASE

void sanitize(char *str);

int main(){
    struct sockaddr_in saddr;
    // struct hostent *hp;
    // char hostname[HOSTLEN];
    int sock_id,sock_fd;
    FILE *sock_fpi, *sock_fpo;
    FILE *pipe_fp;
    char dirname[BUFSIZ];
    char command[BUFSIZ];
    int c;

    /*
     * Step 1: ask kernel for a socket
     */
    sock_id = socket(AF_INET, SOCK_STREAM, 0 );
    if( sock_id == -1 ){
        oops("socket");
    }

    /*
     * Step 2: bind address to socket. Address is host,port
     */
    bzero((void*)&saddr,sizeof(saddr));
    // gethostname(hostname,HOSTLEN);
    // hp = gethostbyname(hostname);
    // bcopy((void*)hp->h_addr,(void*)&saddr.sin_addr,hp->h_length);

    saddr.sin_addr.s_addr = inet_addr(ADDRESS);
    saddr.sin_port = htons(PORTNUM);
    saddr.sin_family = AF_INET;

    if( bind(sock_id, (struct sockaddr *)&saddr, sizeof(saddr)) != 0){
        oops("bind");
    }

    /*
     * Step 3: allow incoming calls with Qsize=1 on socket
     */
    if( listen(sock_id,1) != 0 ){
        oops("listen");
    }

    /*
     * main loop: accept(), write(), close()
     */
    while(1){
        sock_fd = accept(sock_id,NULL,NULL);
        if( sock_fd == -1 ){
            oops("accept");
        }
#if RUNTYPE == DEBUG
        printf("Get a call");
#endif
        if( (sock_fpi = fdopen(sock_fd,"r")) == NULL ){
            oops("fdopen reading");
        }

        if( fgets(dirname,BUFSIZ - 5, sock_fpi) == NULL ){
            oops("reading dirname");
        }
#if RUNTYPE == DEBUG
        printf("Get dir:\n%s\n",dirname);
#endif
        sanitize(dirname);

        if( (sock_fpo = fdopen(sock_fd,"w")) == NULL){
            oops("fdopen writing");
        }

        sprintf(command,"ls %s",dirname);
        if( (pipe_fp = popen(command,"r")) == NULL ){
            oops("popen");
        }

        // char buf[BUFSIZ];
        // fgets(buf,BUFSIZ,pipe_fp);
        // write(sock_fd,buf,strlen(buf));
        while( (c = getc(pipe_fp) ) != EOF ){
#if RUNTYPE == DEBUG
            putchar(c);
#endif
            putc(c,sock_fpo);
        }
#if RUNTYPE == DEBUG
        printf("send complete\n");
#endif
        fflush(sock_fpo);
        pclose(pipe_fp);
        fclose(sock_fpi);
        fclose(sock_fpo);
    }
    return 0;
}

void sanitize(char *str){
    char *src, *dest;
    for(src = dest = str; *src;src++){
        if( *src == '/' || isalnum(*src) || *src == '_' || *src == '-' || *src == '.' || *src == '+'){
            *dest++ = *src;
        }
    }
    *dest = '\0';
}
