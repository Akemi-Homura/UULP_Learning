# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>

# define PRONAME "isaregfile"
# define oops(m,x) {perror(m); exit(x);}

int main(int argc,char **argv){
    if(argc != 2){
        fprintf(stderr,"usage: %s filepath\n",PRONAME);
        exit(1);
    }

    const char* filepath = argv[1];
    int fd;

    if((fd = open(filepath,O_RDONLY)) == -1){
        oops("open",2);
    }

    struct stat s_buf;
    if(fstat(fd,&s_buf) == -1){
        oops("fstat",3);
    }

    if(S_ISREG(s_buf.st_mode)){
        printf("%s is a regular file\n",filepath);
    }else{
        printf("%s is not a regular file\n",filepath);
    }
    return 0;
}
