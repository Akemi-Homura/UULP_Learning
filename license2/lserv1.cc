# include "lserv_funcs1.h"
# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <signal.h>
# include <sys/errno.h>

# define MSGLEN 128

int main(){
    struct sockaddr_in client_addr;
    socklen_t addrlen = sizeof(client_addr);
    char buf[MSGLEN];
    int  ret;
    int  sock;
    unsigned time_left;

    sock = setup();
    signal(SIGALRM, ticket_reclaim);
    alarm(RECLAIM_INTERVAL);

    while(1){
        addrlen = sizeof(client_addr);
        ret = recvfrom(sock,buf,MSGLEN,0,(struct sockaddr*)&client_addr,&addrlen);
        if( ret != -1 ){
            buf[ret] = '\0';
            narrate("GOT:", buf, &client_addr);
            time_left = alarm(0);
            handle_request(buf,(struct sockaddr*)&client_addr,addrlen);
            alarm(time_left);
        }else if( errno != EINTR ){
            perror("recvfrom");
        }
    }
}
