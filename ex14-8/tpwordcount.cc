# include <stdio.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>

# define PRONAME "tpwordcount"
# define oops(msg) {perror(msg); exit(1);}
# define RELEASE    1
# define DEBUG      0
# define RUNTYPE    RELEASE

void count_word(const char*,int);

int main(int ac,char **av){
    if(ac < 2){
        fprintf(stderr,"usage: %s file ...\n",PRONAME);
        exit(1);
    }

    int filenum = ac - 1;
    int apipe[2];
    if(pipe(apipe) == -1){
        oops("pipe");
    }
    for(int i=0;i<filenum;i++){
        count_word(av[i+1],apipe[1]);
    }

    for(int i=0;i<filenum;i++){
        if(wait(NULL) == -1){
            oops("wait");
        }
    }

    char buf[BUFSIZ];
    FILE* fp = fdopen(apipe[0],"r");
    int total_words = 0;
    int rdtimes = 0;
    int aword;
    while(fgets(buf,BUFSIZ,fp) != NULL){
        sscanf(buf,"%d%s",&aword,buf);
        printf("%4d %s\n",aword,buf);
        total_words += aword;
        if(++rdtimes == filenum){
            break;
        }
    }

    printf("%4d total\n",total_words);
    return 0;
}

void count_word(const char* filename,int fd){
#if RUNTYPE == DEBUG
    printf("filename: %s\n",filename);
#endif
    int pid = fork();
    if(pid == -1){
        oops("fork");
    }else if(pid == 0){
        dup2(fd,STDOUT_FILENO);
        dup2(fd,STDERR_FILENO);
        close(fd);
        execlp("wc","wc","-w",filename,NULL);
        perror("wc");
        exit(1);
    }
}
