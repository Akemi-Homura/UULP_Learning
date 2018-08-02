# include "screensz.h"

# define oops(s,x) {perror(s); exit(x);}
# define TTY "/dev/tty"

void get_winsize(int&row,int&col){
    int fd = open(TTY,O_RDONLY);
    struct winsize wbuf;
    if(ioctl(fd,TIOCGWINSZ,&wbuf) == -1){
        oops("ioctl",1);
    }
    row = wbuf.ws_row;
    col = wbuf.ws_col;
}
