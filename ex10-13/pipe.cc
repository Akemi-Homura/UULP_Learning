# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

# define oops(m,x) {perror(m); exit(x);}

void createpipe(int tot,int now,char** argv);

int main(int argc, char**argv){
    if(argc < 3){
        fprintf(stderr,"usage: pipe cmd1 cmd2 ...\n");
        exit(1);
    }
    createpipe(argc,1,argv);
    return 0;
}

void createpipe(int tot,int now,char **argv){
    if(now == tot-1) return;

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
        createpipe(tot,now+1,argv);
        execlp(argv[now+1],argv[now+1],NULL);
        oops(argv[now+1],4);
    }

    close(thepipe[0]);
    if(dup2(thepipe[1],1) == -1){
        oops("could not redirect stdout",4);
    }
    close(thepipe[1]);
    execlp(argv[now],argv[now],NULL);
    oops(argv[now],5);
}
