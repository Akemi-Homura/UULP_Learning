# ifndef LSERV_FUNCS1_h
# define LSERV_FUNCS1_h

# include <sys/types.h>
# include <sys/socket.h>

int setup();

void narrate(const char*,const char*,struct sockaddr_in*);

void handle_request(const char*,struct sockaddr*,socklen_t);

# endif
