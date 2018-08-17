# include "lserv_funcs1.h"
# include "dgram.h"
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <arpa/inet.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <netdb.h>
# include <signal.h>
# include <sys/errno.h>

# define SERVER_PORTNUM 13000
# define MSGLEN         128
# define TICKET_AVAIL   0
# define MAXUSERS       3
# define oops(x) {perror(x); exit(-1);}

/*
 * Important variables
 */
static int ticket_array[MAXUSERS];
static int sd = -1;
static int num_tickets_out = 0;

static const char *do_hello(const char*);
static const char *do_goodbye(const char*);
static const char* do_validate(const char*msg);

static void free_all_tickets();

int setup(){
    sd = make_dgram_server_socket(SERVER_PORTNUM);
    if( sd == -1 ){
        oops("make socket");
    }
    free_all_tickets();
    return sd;
}

void free_all_tickets(){
    for(int i=0;i<MAXUSERS;i++){
        ticket_array[i] = TICKET_AVAIL;
    }
}

void handle_request(const char* req,struct sockaddr* client,socklen_t addlen){
    const char *response;
    int ret;
    /*
     * act and compose a response
     */
    if( strncmp(req,"HELO", 4) == 0){
        response = do_hello(req);
    }else if( strncmp(req,"GBYE",4) == 0 ){
        response = do_goodbye(req);
    }else if( strncmp(req,"VALD",4) == 0 ){
        response = do_validate(req);
    }
    else{
        response = "FAIL invalid request";
    }

    /*
     * send the response to the clinet
     */
    narrate("SAID:",response,(struct sockaddr_in*)client);
    ret = sendto(sd, response, strlen(response), 0, client, addlen);
    if ( ret == -1 ){
        perror("SERVER sendto failed");
    }
}

const char *do_hello(const char* msg_p){
    int x;
    static char replybuf[MSGLEN];

    if(num_tickets_out >=  MAXUSERS){
        return "FAIL no tickets available";
    }

    for(x = 0;x < MAXUSERS && ticket_array[x] != TICKET_AVAIL;x++);

    /*
     * a sanity check - should never happen
     */
    if( x == MAXUSERS ){
        narrate("database corrupt","",NULL);
        return "FAIL database corrupt";
    }

    /*
     * Found a free ticket.Record "name" of user (pid) in array.
     * generate ticket of form: pid.slot
     */
    ticket_array[x] = atoi(msg_p + 5); /* get pid in msg */
    sprintf(replybuf, "TICK %d.%d",ticket_array[x],x);
    ++num_tickets_out;
    return replybuf;
}

const char* do_goodbye(const char* msg_p){
    int pid,slot;

    /*
     * The user's giving us back a ticket. First we need to get the ticket out
     * of the message,which looks like
     *
     * GBYE pid.slot
     */
    if(sscanf(msg_p + 5,"%d.%d",&pid,&slot) != 2 || ticket_array[slot] != pid){
        narrate("Bogus ticket", msg_p + 5, NULL);
        return "FAIL invalid ticket";
    }

    /*
     * The ticket is valid. Release it
     */
    ticket_array[slot] = TICKET_AVAIL;
    --num_tickets_out;

    return "THNX See ya!";
}

void narrate(const char* msg1,const char* msg2,struct sockaddr_in* clientp){
    fprintf(stderr, "\t\tSERVER: %s %s",msg1,msg2);

    if(clientp){
        fprintf(stderr,"(%s:%d)",inet_ntoa(clientp->sin_addr),ntohs(clientp->sin_port));
    }
    putc('\n',stderr);
}

void ticket_reclaim(int){
    char tick[BUFSIZ];

    for(int i=0;i < MAXUSERS; i++ ){
        if(ticket_array[i] != TICKET_AVAIL && kill(ticket_array[i],0) == -1 && errno == ESRCH){
            /*
             * Process is gone - free up slot
             */
            sprintf(tick,"%d.%d",ticket_array[i],i);
            narrate("freeeing",tick,NULL);
            ticket_array[i] = TICKET_AVAIL;
            --num_tickets_out;
        }
    }

    alarm(RECLAIM_INTERVAL);
}

const char* do_validate(const char* msg){
    int pid,slot;
    if( sscanf(msg+5,"%d.%d",&pid,&slot) == 2 && ticket_array[slot] == pid){
        return "GOOD Valid ticket";
    }

    /*
     * bad ticket
     */
    narrate("Bogus ticket",msg + 5, NULL);
    return "FAIL invalid ticket";
}
