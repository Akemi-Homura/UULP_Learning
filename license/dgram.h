# ifndef DGRAM_H
# define DGRAM_H

int make_dgram_server_socket(int);

int get_internet_address(char*,int,int*,struct sockaddr_in*);

int make_dgram_client_socket();

int make_internet_address(const char*,int,struct sockaddr_in *);

# endif
