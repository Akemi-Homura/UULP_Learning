# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# define DEFAULTLINE 10
# define ARGU_COUNT "-n"
# define BUFFERSIZE 4096

void display(const char*,int);
void check_permission(const char*);

int main(int argc,char * argv[]){
    int show_lines = DEFAULTLINE;
    if(argc == 4){
        if(strcmp(argv[1],ARGU_COUNT) != 0){
            fprintf(stderr,"head: illegal option -- %s\n",argv[1]);
            fprintf(stderr,"usage: head [-n lines] [file]\n");
            exit(1);
        }
        show_lines = atoi(argv[2]);
        display(argv[3],show_lines);
    }else if(argc == 2){
        display(argv[1],show_lines);
    }else {
        fprintf(stderr,"usage: head [-n lines] [file]\n");
        exit(1);
    }
}

void display(const char *path,int lines){
    check_permission(path);
    FILE* file = fopen(path,"r");
    char buf[BUFFERSIZE];
    while(fgets(buf,BUFFERSIZE,file) != NULL && lines -- ){
        printf("%s",buf);
    }
    if(ferror(file)!=0){
        fprintf(stderr,"Error: read error ");
        perror(path);
    }
}

void check_permission(const char*path){
    if(access(path,F_OK) == -1){
        fprintf(stderr,"%s not exists\n",path);
        exit(1);
    }
    if(access(path,R_OK) == -1){
        fprintf(stderr,"Error: Can't read ");
        perror(path);
        exit(1);
    }
}
