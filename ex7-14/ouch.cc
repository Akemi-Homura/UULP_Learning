# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include <stdlib.h>

# define SLPTIME 1
# define PRONAME "ouch"

char * msg;
int times;

void show_usage(const char* );

int main(int argc,char** argv){
    void f(int);
    signal(SIGINT,f);

    if(argc != 3){
        show_usage(PRONAME);
        exit(0);
    }

    msg = argv[1];
    times = atoi(argv[2]);

    while(1){
        pause();
    }
    return 0;
}

void f(int){
    static int num = 0;
    if(++num == times){
        printf("%s\n",msg);
        num = 0;
    }
}

void show_usage(const char* pro){
    fprintf(stderr,"usage: %s msg time\n",pro);
}
