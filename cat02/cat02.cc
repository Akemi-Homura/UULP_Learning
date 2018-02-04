# include <stdio.h>
# include <stdlib.h>

# define BUFFERSIZE 4096

void oops(const char *,const char *);
void display(const char *);

int main(int argc,char* argv[]){
    if(argc == 1){
        fprintf(stderr,"usage: %s file\n",argv[0]);
        exit(1);
    }
    FILE* file;
    if((file = fopen(argv[1],"r")) == NULL){
        oops("Can't open ",argv[1]);
    }
    char buf[BUFFERSIZE];
    while(fgets(buf,BUFFERSIZE,file) != NULL){
        display(buf);
    }
    if(ferror(file) != 0){
        oops("Read file error ",argv[1]);
    }
    return 0;
}

void display(const char *msg){
    printf("%s",msg);
}

void oops(const char* s1,const char * s2){
    fprintf(stderr,"Error: %s ",s1);
    perror(s2);
    exit(1);
}
