# include <stdio.h>
# include <unistd.h>
# include <signal.h>

# define SLPTIME 1

int main(){
    void f(int);
    signal(SIGINT,f);

    for(int i=0;i<5;i++){
        printf("Hello\n");
        sleep(SLPTIME);
    }
    return 0;
}

void f(int signum){
    if(signum == SIGINT){
        printf("OUCH! FUCK YOU,BITCH!\n");
    }
}
