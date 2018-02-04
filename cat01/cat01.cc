# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# define BUFFERSIZE 4096

void oops(const char *,const char *);
void display(const char*);

int main(int argc,char *argv[]){
    if(argc == 1){
        fprintf(stderr,"usage: %s file\n",argv[0]);
        exit(1);
    }
    int fd;
    if((fd = open(argv[1],O_RDONLY)) == -1){
        oops("Can't open ",argv[1]);
    }
    char buf[BUFFERSIZE + 1];
    int n_chars;
    while((n_chars = read(fd,buf,BUFFERSIZE)) > 0){
        buf[n_chars] = '\0';
        display(buf);
    }
    if(n_chars == -1){
        oops("Read error ",argv[1]);
    }
    return 0;
}

void display(const char *msg){
    printf("%s",msg);
}

void oops(const char *s1,const char *s2){
    fprintf(stderr,"Error: %s ",s1);
    perror(s2);
    exit(1);
}
