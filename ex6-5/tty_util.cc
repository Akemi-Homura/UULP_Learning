# include "tty_util.h"
# include <unistd.h>
# include <fcntl.h>
# include <termios.h>
# include <stdlib.h>
# include <stdio.h>

# define oops(s,x) {perror(s); exit(1);}
# define DFLFD 0

void tty_mode(int how){
    static struct termios origin_termios;
    static int origin_file_status;
    static bool has_saved = false;

    if(how == TTY_MODE_SAVE){
        if( (origin_file_status = fcntl(DFLFD,F_GETFL)) == -1){
            oops("fcntl F_GETFL",1);
        }
        if( tcgetattr(DFLFD,&origin_termios) == -1){
            oops("tcgetattr",1);
        }
        has_saved = true;
    }

    if(how == TTY_MODE_RESET){
        if(!has_saved){
            fprintf(stderr,"Can't reset tty mode,since tty mode has not saved!\n");
            exit(1);
        }
        if(fcntl(DFLFD,F_SETFL,origin_file_status) == -1){
            oops("fcntl F_SETFL",1);
        }
        if(tcsetattr(DFLFD,TCSANOW,&origin_termios) == -1){
            oops("tcsetattr",1);
        }
    }
}

void set_no_echo(){
    struct termios ttystatus;
    if(tcgetattr(DFLFD,&ttystatus) == -1){
        oops("tcgetattr",1);
    }
    ttystatus.c_lflag &= ~( ICANON | ECHO );

    ttystatus.c_cc[VMIN] = 1;
    if(tcsetattr(DFLFD,TCSANOW,&ttystatus) == -1){
        oops("tcsetattr",1);
    }
}

void set_no_delay(){
    int file_des_flags;
    if((file_des_flags = fcntl(DFLFD,F_GETFL)) == -1){
        oops("fcntl F_GETFL",1);
    }
    file_des_flags |= O_NONBLOCK;
    if(fcntl(DFLFD,F_SETFL,file_des_flags) == -1){
        oops("fcntl F_SETFL",1);
    }
}
