# include <signal.h>
# include <stdio.h>
# include <unistd.h>
# include <termios.h>
# include <unistd.h>
# include <stdlib.h>

# define oops(s,x) {perror(s); exit(x);}
# define DFLFD 0

void set_no_isig();

int main(){
    set_no_isig();
    while(1){
        sleep(1);
        printf("haha\n");
    }
    return 0;
}

void set_no_isig(){
    struct termios stat;
    if(tcgetattr(DFLFD,&stat) == -1){
        oops("tcgetattr",1);
    }
    stat.c_lflag &= ~ISIG;
    if(tcsetattr(DFLFD,TCSANOW,&stat) == -1){
        oops("tcsetattr",1);
    }
}
