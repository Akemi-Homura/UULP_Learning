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
        printf("")
    }
}
