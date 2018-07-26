# include <stdio.h>
# include <ctype.h>
# include "tty_util.h"
# include <stdlib.h>

int main(){
    tty_mode(TTY_MODE_SAVE);
    set_no_echo();
    set_no_delay();
    char c;
    int eoftimes = 0;
    while( (c = getchar()) ){
        if(c == EOF){
            printf("Get a EOF\n");
            ++eoftimes;
        }
        if(eoftimes >= 10000){
            exit(1);
        }
        fflush(stdout);
        if(c == 'Q'){
            return 0;
        }
        if( c == 'z' ){
            c = 'a';
        }else if(islower(c)){
            ++c;
        }
        putchar(c);
    }
    tty_mode(TTY_MODE_RESET);
    return 0;
}
