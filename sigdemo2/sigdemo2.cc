# include <signal.h>
# include <stdio.h>
# include <unistd.h>

int main(){
    signal(SIGINT,SIG_IGN);
    printf("You can't stop me! Bitch!\n");

    while(1){
        sleep(1);
        printf("haha\n");
    }
    return 0;
}
