# include "screensz.h"
# include <sys/ioctl.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>

# define oops(s,x) {perror(s); exit(x);}
# define TTY "/dev/tty"

int get_row_num(){
    int fd = open(TTY,O_RDONLY);
    struct winsize wbuf;
    if(ioctl(fd,TIOCGWINSZ,&wbuf) == -1){
        oops("ioctl",1);
    }
    return wbuf.ws_row;
}
