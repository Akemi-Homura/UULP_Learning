# include <stdio.h>
# include <termios.h>
# include <stdlib.h>

# define oops(s,x) {perror(s); exit(x);}

int main(){
    struct termios info;
    if(tcgetattr(0,&info) == -1){
        oops("tcgetattr",1);
    }

    if(info.c_oflag & OLCUC){
        printf("OLCUC is on, since its bit is 1\n");
    }else{
        printf("OLCUC is off, sinze its bit is 0\n");
    }
    return 0;
}
