# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# define FILENAME "info.txt"
# define RDLEN 20

void oops(const char*,const char*);

int main(){
    int fd1,fd2,fd3;
    if((fd1 = open(FILENAME,O_RDONLY)) == -1){
        oops("fd1: Can't open ",FILENAME);
    }
    if((fd2 = open(FILENAME,O_WRONLY)) == -1){
        oops("fd2: Can't open ",FILENAME);
    }
    if((fd3 = open(FILENAME,O_RDONLY)) == -1){
        oops("fd3: Can't open ",FILENAME);
    }

    char buf_rd[RDLEN];
    if(read(fd1,buf_rd,RDLEN) != RDLEN){
        oops("fd1: Read error ",FILENAME);
    }
    if(close(fd1) == -1){
        oops("fd1: Close error ",FILENAME);
    }
    printf("fd1 reads:\n%s\n",buf_rd);

    const char *buf_wr = "testing 1234455660187897891";
    int wr_len = strlen(buf_wr);
    if(write(fd2,buf_wr,wr_len) != wr_len){
        oops("fd2: Write error ",FILENAME);
    }
    if(close(fd2) == -1){
        oops("fd2: Close error ",FILENAME);
    }

    if(read(fd3,buf_rd,RDLEN) != RDLEN){
        oops("fd3: Read Error ",FILENAME);
    }
    printf("fd3 reads:\n%s\n",buf_rd);
    if(close(fd3) == -1){
        oops("fd3: Close error ",FILENAME);
    }
    return 0;
}

void oops(const char *s1,const char* s2){
    fprintf(stderr,"Error: %s",s1);
    perror(s2);
    exit(1);
}
