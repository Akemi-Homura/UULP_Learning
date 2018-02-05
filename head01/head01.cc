# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# define DEFAULTLINE 10
# define ARGU_COUNT "-n"
# define BUFFERSIZE 4096
# define FILEINO "==> %s <==\n"

void display(const char*,int);
bool check_permission(const char*);
void show_usage();

int main(int argc,char * argv[]){
    if(argc == 1) {
        show_usage();
        exit(1);
    }
    int show_lines = DEFAULTLINE;
    int file_index = 1;
    if(strcmp(argv[1],ARGU_COUNT) == 0){
        file_index = 3;
        if(argc < 3){
            fprintf(stderr,"head: option requires an argument --n\n");
            show_usage();
            exit(1);
        }
        show_lines = atoi(argv[2]);
    }else if(argv[1][0] == '-'){
        fprintf(stderr,"head: illegal option -- %s\n",argv[1]+1);
        show_usage();
        exit(1);
    }

    for(int i = file_index; i < argc ;i ++){
        if(!check_permission(argv[i])){
            continue;
        }
        if(i > file_index){
            printf("\n");
        }
        if(argc > file_index){
            printf(FILEINO,argv[i]);
        }
        display(argv[i],show_lines);
    }
    return 0;
}

void show_usage(){
    fprintf(stderr,"usage: head [-n lines] [file]\n");
}

void display(const char *path,int lines){
    FILE* file = fopen(path,"r");
    char buf[BUFFERSIZE];
    while(fgets(buf,BUFFERSIZE,file) != NULL && lines -- ){
        printf("%s",buf);
    }
    if(ferror(file)!=0){
        fprintf(stderr,"Error: read error ");
        perror(path);
    }
    fclose(file);
}

bool check_permission(const char*path){
    if(access(path,F_OK) == -1){
        fprintf(stderr,"head: %s: No such file.\n",path);
        return false;
    }else if(access(path,R_OK) == -1){
        fprintf(stderr,"Error: Can't read ");
        perror(path);
        fprintf(stderr,"\n");
        return false;
    }
    return true;
}
