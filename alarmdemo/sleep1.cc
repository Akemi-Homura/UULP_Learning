# include <signal.h>
# include <stdio.h>
# include <unistd.h>

# define SHHH

int main(){
    void wakeup(int);

    printf("about to sleep 4 seconds\n");
    signal(SIGALRM,wakeup);
    alarm(4);
    pause();
    printf("Morning so soon? \n");
    return 0;
}

void wakeup(int){
#ifdef SHHH
    printf("Alarm reveived from kernel\n");
#endif
}
