# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>

# define PRONAME "tpwordcount"
# define oops(msg) {perror(msg); exit(1);}

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
        count_word()
    }
}
