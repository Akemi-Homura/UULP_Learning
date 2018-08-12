# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

# define oops(m,x) {perror(m); exit(x);}

void createpipe(const char* cmd1,const char* cmd2){
    int thepipe[2],
        pid;

    if(pipe(thepipe) == -1){
        oops("Cannot get a pipe",1);
    }

    if( (pid = fork()) == -1){
        oops("Cannot fork",2);
    }

    if( pid > 0 ){
        close(thepipe[1]);
        if(dup2(thepipe[0],0) == -1){
            oops("could not redirect stdin",3);
        }
        close(thepipe[0]);
        execlp(cmd2,cmd2,NULL);
        oops(cmd2,4);
    }

    close(thepipe[0]);
    if(dup2(thepipe[1],1) == -1){
        oops("could not redirect stdout",4);
    }
    close(thepipe[1]);
    execlp(cmd1,cmd1,NULL);
    oops(cmd1,5);
}

int main(int argc, char**argv){
    if(argc < 3){
        fprintf(stderr,"usage: pipe cmd1 cmd2...\n");
        exit(1);
    }

    for(int i=1;i<argc-1;i++){
        createpipe(argv[i],argv[i+1]);
    }

    return 0;
}
