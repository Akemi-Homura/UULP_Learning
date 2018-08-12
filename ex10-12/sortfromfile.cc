# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>

# define oops(m,x) {perror(m); exit(x);}
# define SORT "sort"
# define PRONAME "sortfromfile"

int main(int argc,char** argv){
    if(argc!=2){
        fprintf(stderr,"usage: %s filename\n",PRONAME);
        exit(1);
    }
    const char *filename = argv[1];

    int fd;
    if((fd = open(filename,O_RDONLY) == -1)){
        oops("open",2);
    }

    // redirect
    if(dup2(fd,STDIN_FILENO) == -1){
        oops("dup2",3);
    }
    close(fd);

    execlp(SORT,SORT,filename,NULL);
    oops("execlp",4);
    return 0;
}
