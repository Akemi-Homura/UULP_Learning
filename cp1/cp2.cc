# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>

# define BUFFERSIZE 4096
# define COPYMODE 0644
# define ARGUVER "-i"
# define OVERWRITEINFO "overwrite %s? (y/n [n])"
# define NOTOVERWRITE "not overwritten\n"

void oops(const char*,const char*);
void copy_file(const char*,const char*);
bool is_file_exist(const char*);

int main(int argc,char *argv[]){
    if(argc == 4){
        if(strcmp(argv[1],ARGUVER) != 0){
            fprintf(stderr,"Unkown argument %s\n",argv[1]);
            exit(1);
        }
        if(is_file_exist(argv[3])){
            printf(OVERWRITEINFO,argv[3]);
            char c = getchar();
            if(c == 'y'){
                copy_file(argv[2],argv[3]);
            }else{
                printf(NOTOVERWRITE);
            }
        }else{
            copy_file(argv[2],argv[3]);
        }
    } else if(argc == 3){
        copy_file(argv[1],argv[2]);
    }
    else{
        fprintf(stderr,"usage: %s source destination\n", *argv);
        exit(1);
    }
}

void copy_file(const char * src, const char * dst){
    int in_fd,out_fd,n_chars;
    char buf[BUFFERSIZE];

    if((in_fd = open(src,O_RDONLY)) == -1){
        oops("Can't open ",src);
    }

    if((out_fd = creat(dst,COPYMODE)) == -1){
        oops("Can't open ",dst);
    }

    while((n_chars = read(in_fd,buf,BUFFERSIZE)) > 0){
        if(write(out_fd,buf,n_chars) != n_chars){
            oops("Write error to ",dst);
        }
    }

    if(n_chars == -1){
        oops("Read error from ",src);
    }
    if(close(in_fd) == -1 || close(out_fd) == -1){
        oops("Error closing files","");
    }
}

void oops(const char * s1,const char * s2){
    fprintf(stderr,"Error: %s",s1);
    perror(s2);
    exit(1);
}

bool is_file_exist(const char * filename){
    return access(filename,W_OK) == 0;
}
