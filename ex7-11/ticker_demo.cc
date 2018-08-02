# include <stdio.h>
# include <sys/time.h>
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>

# define DFLTIME 500

int set_ticker(int);

bool done;

int main(){
    done = false;
    void countdown(int);

    signal(SIGALRM,countdown);
    if( set_ticker(DFLTIME) == -1 ){
        perror("set_ticker");
    }else{
        while(!done){
            pause();
        }
    }
    return 0;
}

void countdown(int){
    static int num = 10;
    printf("%d..",num--);
    fflush(stdout);
    if( num < 0){
        printf("DONE! \n");
        done = true;
    }
}

int set_ticker(int n_msecs){
    struct itimerval new_timeset;
    long n_sec, n_usecs;

    n_sec = n_msecs / 1000;
    n_usecs = (n_msecs % 1000) * 1000L;

    new_timeset.it_interval.tv_sec = n_sec;
    new_timeset.it_interval.tv_usec = n_usecs;

    new_timeset.it_value.tv_sec = n_sec;
    new_timeset.it_value.tv_usec = n_usecs;

    return setitimer(ITIMER_REAL,&new_timeset,NULL);
}
