# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include <stdlib.h>

# define SLPTIME 5

int terminate_time;

int main(int argc,char** argv){
    void f(int);
    signal(SIGINT,f);
    if(argc == 1){
        terminate_time = 2;
    }else{
        terminate_time = atoi(argv[1]);
        if(terminate_time < 1){
            terminate_time = 1;
        }
    }
    while(1){
        printf("Hello\n");
        sleep(SLPTIME);
    }
    return 0;
}

void f(int ){
    static int tot = 0;
    ++tot;
    printf("OUCH");
    for(int i=0;i<tot;i++){
        putchar('!');
    }
    putchar('\n');
    if(--terminate_time == 0){
        exit(0);
    }
}
