/*
 * logfilec.cc - logfile client - send message to the logfile server
 * usage: logfile "a message here"
 */

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <pwd.h>
# include <sys/socket.h>
# include <sys/un.h>

# define SOCKET "/tmp/logfilesock"
# define oops(m,x) { perror(m); exit(x); }

# define RELEASE 0
# define DEBUG   1
# define RUNTYPE RELEASE

const char* getusername();

int main(int ac,char **av){
    int                 sock;
    struct sockaddr_un  addr;
    socklen_t           addrlen;
    const char*         socketname = SOCKET;
    char *              msg = av[1];
    char buf[BUFSIZ];

    if( ac != 2){
        fprintf(stderr,"usage : logfile 'message'\n");
        exit(1);
    }
    sock = socket(AF_UNIX, SOCK_DGRAM, 0);
    if( sock == -1 ){
        oops("socket",2);
    }

    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path,socketname);
    addrlen = strlen(socketname) + sizeof(addr.sun_family);

    const char* username = getusername();
    sprintf(buf,"[%s]: %s",username,msg);
#if RUNTYPE == DEBUG
    printf("username: %s\n",username);
#endif

    if( sendto(sock, buf, strlen(buf), 0, (struct sockaddr*)&addr, addrlen) == -1 ){
        oops("sendto",3);
    }
    return 0;
}

const char* getusername(){
    int euid = geteuid();
    passwd* record = getpwuid(euid);
    return record->pw_name;
}
