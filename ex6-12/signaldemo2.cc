# include <signal.h>
# include "screensz.h"
# include "tty_util.h"

# define BEEP putchar('\a')

# define RELEASE 0
# define DEBUG   1
# define RUNTYPE RELEASE

void winch_handler(int);
int  cal_char_nums(struct winsize);
void EXIT(int);

int main(){
    tty_mode(TTY_MODE_SAVE);
    set_no_echo();
    signal(SIGWINCH,winch_handler);

    char c;
    while( ( c = getchar() ) != EOF){
        if( c == 'Q'){
            EXIT(0);
        }
    }
    return 0;
}

void EXIT(int v){
    tty_mode(TTY_MODE_RESET);
    exit(v);
}

void winch_handler(int){
    printf("\33[2J");
    printf("\33[H");

    static char c = 'A';
    struct winsize info = get_winsize();
    int sum = cal_char_nums(info);

    for(int i=0;i<sum;i++){
        putchar(c);
    }
    fflush(stdout);

    if(c == 'Z'){
        c = 'A';
    }else{
        ++c;
    }
#if RUNTYPE == DEBUG
    printf("row:%d col:%d size:%d\n",info.ws_row,info.ws_col,sum);
#endif
}

int cal_char_nums(struct winsize info){
    return info.ws_row * info.ws_col;
}
