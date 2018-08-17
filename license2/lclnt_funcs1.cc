# include "lclnt_funcs1.h"
# include "dgram.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <strings.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netdb.h>
# include <netinet/in.h>

static pid_t pid = -1;
static int sd  = -1;
static struct sockaddr serv_addr;
static socklen_t serv_alen;
static char ticket_buf[128];
static int have_ticket = 0;

# define MSGLEN         128
# define SERVER_PORTNUM 13000
# define HOSTLEN        512
# define oops(p) {perror(p); exit(1);}

# define RELEASE 0
# define DEBUG   1
# define RUNTYPE DEBUG

char *do_transaction(const char*);
void narrate(const char*,const char*);
void syserr(const char*);

void setup(){
    char hostname[HOSTLEN];

    pid = getpid();
    sd = make_dgram_client_socket();
    if( sd == -1 ){
        oops("Cannot create socket");
    }
    gethostname(hostname,HOSTLEN);
    make_internet_address(hostname,SERVER_PORTNUM,(struct sockaddr_in*)&serv_addr);
    serv_alen = sizeof(serv_addr);
}

void shutdown(){
    close(sd);
}

int get_ticket(){
    char *response;
    char buf[MSGLEN];

    if( have_ticket ){
        return 0;
    }

    sprintf(buf, "HELO %d",pid);

    if( (response = do_transaction(buf)) == NULL){
        return -1;
    }

#if RUNTYPE == RELEASE
    printf("response: %s\n",response);
#endif

    /*
     * parse the response and see if we got a ticket.
     * on success, the message is: TICK ticket-string
     * on failure, the message is: FAIL failure-msg
     */
    if( strncmp(response,"TICK",4) == 0){
        strcpy(ticket_buf,response + 5);
        have_ticket = 1;
        narrate("got ticket", ticket_buf);
        return 0;
    }

    if( strncmp(response,"FAIL",4) == 0){
        narrate("Could not get ticket",response);
    }else{
        narrate("Unknown message:",response);
    }
    return -1;
}

int release_ticket(){
    char buf[MSGLEN];
    char *response;

    if( !have_ticket ){
        return 0;
    }

    sprintf(buf, "GBYE %s",ticket_buf);
    if( (response = do_transaction(buf)) == NULL ){
        return -1;
    }

    /*
     * examine response
     * success: THNX info - string
     * failure: FAIL error - string
     */
    if( strncmp(response, "THNX",4 ) == 0 ){
        narrate("released ticket OK","");
        return 0;
    }

    if( strncmp(response, "FAIL", 4) == 0 ){
        narrate("released failed",response + 5);
    }else{
        narrate("Unkown message:", response);
    }
    return -1;
}

int validate_ticket(){
    if(have_ticket == 0){
        narrate("No ticket to validate","");
        return -1;
    }

    char buf[MSGLEN];
    char *response;

    sprintf(buf,"VALD %s",ticket_buf);
    if((response = do_transaction(buf)) == NULL){
        narrate("Got validate response error","");
        return -1;
    }

    /*
     * examime response
     * success: GOOD info - string
     * failure: FAIL info - string
     */
    if(strncmp(response,"GOOD",4) == 0){
        narrate("Validated ticket:",response);
        return 0;
    }else if(strncmp(response,"FAIL",4) == 0){
        narrate("Validated ticket:",response);
        return -1;
    }
    narrate("Unkown message:",response);
    return -1;
}

char *do_transaction(const char*msg){
    static char buf[MSGLEN];
    struct sockaddr retaddr;
    socklen_t addrlen = sizeof(retaddr);
    int ret;

    ret = sendto(sd, msg, strlen(msg), 0, &serv_addr, serv_alen);
    if( ret == -1 ){
        syserr("sendto");
        return NULL;
    }

    /*
     * Get the response back
     */
    ret = recvfrom(sd,buf,MSGLEN,0,&retaddr,&addrlen);
    if( ret == -1 ){
        syserr("recvfrom");
        return NULL;
    }
    /*
     * Now return the message itself
     */
    return buf;
}

void narrate(const char*msg1,const char* msg2){
    fprintf(stderr,"CLIENT[%d]: %s %s\n",pid,msg1,msg2);
}

void syserr(const char* msg){
    char buf[MSGLEN];
    sprintf(buf,"CLIENT[%d]: %s",pid,msg);
    perror(buf);
}

void shut_down(){
    close(sd);
}
