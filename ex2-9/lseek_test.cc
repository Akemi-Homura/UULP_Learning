# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# define AFENDLEN 20000
# define FILENAME "info.txt"

void oops(const char*,const char*);

int main(){
    int fd;
    if((fd = open(FILENAME,O_WRONLY)) == -1){
        oops("Can't open ",FILENAME);
    }
    if(lseek(fd,AFENDLEN,SEEK_END) == -1){
        oops("Can't reposition ",FILENAME);
    }
    const char * buf_wr = "test";
    int wr_len = strlen(buf_wr);
    if(write(fd,buf_wr,wr_len) != wr_len){
        oops("Write error ",FILENAME);
    }
    if(close(fd) == -1){
        oops("Close error ",FILENAME);
    }
    return 0;
}

void oops(const char * s1, const char * s2){
    fprintf(stderr,"Error: %s ",s1);
    perror(s2);
    exit(1);
}
