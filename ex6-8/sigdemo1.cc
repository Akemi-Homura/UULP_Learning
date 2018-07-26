# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include <stdlib.h>

# define SLPTIME 1
# define ASK "Interupted! OK to quit "

int main(){
    void f(int);
    signal(SIGINT,f);

    for(int i=0;i<5;i++){
        printf("Hello\n");
        sleep(SLPTIME);
    }
    return 0;
}

void f(int){
    char buf[1024];
    while(1){
        printf("%s (y/n)?",ASK);
        scanf("%s",buf);
        if(buf[0] == 'y'){
            exit(0);
        }
        if(buf[0] == 'n'){
            return;
        }
    }
}
