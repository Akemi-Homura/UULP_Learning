# include <stdio.h>
# include <signal.h>
# include <unistd.h>

# define INPUTLEN 100

int main(){
    struct sigaction newhandler;
    sigset_t blocked;
    void inthandler(int);
    char x[INPUTLEN];

    newhandler.sa_handler = inthandler;

    newhandler.sa_flags = SA_RESETHAND | SA_RESTART | SA_NODEFER;

    sigemptyset(&blocked);
    sigaddset(&blocked,SIGQUIT);
    newhandler.sa_mask = blocked;

    if ( sigaction(SIGINT, &newhandler, NULL) == -1 ){
        perror("sigaction");
    }else{
        while(1){
            fgets(x, INPUTLEN, stdin);
            printf("input: %s",x);
        }
    }
}

void inthandler(int s){
    printf("Called with signal %d\n",s);
    sleep(s);
    printf("Done handling signal %d\n",s);
}
