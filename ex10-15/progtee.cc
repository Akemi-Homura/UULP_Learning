# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>

# define PRONAME "progtee"
# define oops(m,x) {perror(m); exit(x);}

int main(int argc, char** argv){
    if(argc != 2){
        fprintf(stderr,"usage: %s cmd\n",PRONAME);
        exit(1);
    }

    int thepipe[2],
        pid;
    char buf[BUFSIZ];

    if(pipe(thepipe) == -1){
        oops("pipe",4);
    }

    if((pid = fork()) == -1){
        oops("fork",2);
    }

    // parent process. Run cmd
    if(pid > 0){
        //redirect stdin
        if(dup2(thepipe[0],STDIN_FILENO) == -1){
            oops("dup2",5);
        }
        close(thepipe[0]);
        close(thepipe[1]);
        execlp(argv[1],argv[1],"-",NULL);
        oops("execlp",3);
    }else{
        FILE* fpout;
        if((fpout=fdopen(thepipe[1],"w")) == NULL){
            oops("fdopen",6);
        }
        close(thepipe[0]);

        while(fgets(buf,BUFSIZ,stdin) != NULL){
            fputs(buf,stdout);
            fputs(buf,fpout);
        }
        fclose(fpout);
    }
    return 0;
}

