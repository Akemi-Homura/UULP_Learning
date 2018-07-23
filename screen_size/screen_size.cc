# include <stdio.h>
# include <sys/ioctl.h>
# include <stdlib.h>
# include <fcntl.h>

# define oops(s,x) {perror(s);exit(1);}

int main(){
    struct winsize wbuf;
    if(ioctl(0,TIOCGWINSZ,&wbuf) == -1){
        oops("ioctl",1);
    }
    printf("%d rows x %d cols\n",wbuf.ws_row,wbuf.ws_col);
    printf("%d wide x %d tall\n",wbuf.ws_xpixel,wbuf.ws_ypixel);
    return 0;
}
