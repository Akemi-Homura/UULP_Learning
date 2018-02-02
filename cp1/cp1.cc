# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

# define BUFFERSIZE 4096
# define COPYMODE 0644

void oops(const char*,char*);

int main(int argc,char *argv[]){
    int in_fd,out_fd,n_chars;
    char buf[BUFFERSIZE];

    if(argc != 3){
        fprintf(stderr,"usage: %s source destination\n", *argv);
        exit(1);
    }

    if((in_fd = open(argv[1],O_RDONLY)) == -1){
        oops("Can't open ",argv[1]);
    }

    if((out_fd = open(argv[2],O_WRONLY)) == -1){
        oops("Can't open ",argv[2]);
    }

    while((n_chars = read(in_fd,buf,BUFFERSIZE)) > 0){
        if(write(out_fd,buf,n_chars) != n_chars){
            oops("Write error to ",argv[2]);
        }
    }
    return 0;
}

void oops(const char * s1, const char * s2){
    fprintf(stderr,"Error: %s %s",s1,s2);
    exit(1);
}
