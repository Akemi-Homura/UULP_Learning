# include <stdio.h>
# include <termios.h>
# include "error_process.h"

int main(){
    struct termios info;
    if(tcgetattr(0,&info) == -1){
        perror("tcgetattr");
        exit(1);
    }

    if(info.c_lflag & ECHO){
        printf("echo is on, since its bit is 1\n");
    }else{
        printf("echo is off, since its bit is 0\n");
    }
    return 0;
}
