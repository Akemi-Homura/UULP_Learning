# include "screensz.h"

# define oops(s,x) {perror(s); exit(x);}
# define TTY "/dev/tty"

struct winsize get_winsize(){
    int fd = open(TTY,O_RDONLY);
    struct winsize wbuf;
    if(ioctl(fd,TIOCGWINSZ,&wbuf) == -1){
        oops("ioctl",1);
    }
    return wbuf;
}
