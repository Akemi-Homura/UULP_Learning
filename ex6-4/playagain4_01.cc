# include <stdio.h>
# include <signal.h>
# include "tty_util.h"
# include <string.h>
# include <stdlib.h>
# include <unistd.h>

# define ASK "Do you want another translation"
# define TRIES 3
# define SLPTIME 2
# define BEEP putchar('\a')
# define C_YES 'y'
# define C_NO  'n'
# define RES_YES 0
# define RES_NO  1
# define RES_OUTTIME 2
# define OK_CHARS "yYnN"

int get_response(const char*,int );
int get_ok_char();

int main(){
    tty_mode(TTY_MODE_SAVE);
    set_no_echo();
    set_no_delay();

    void ctrl_c_handler(int);
    signal(SIGINT,SIG_IGN);
    signal(SIGQUIT,SIG_IGN);
    int res = get_response(ASK,TRIES);
    tty_mode(TTY_MODE_RESET);
    return res;
}

int get_response(const char* question,int maxtries){
    int input;
    printf("%s(y/n)?\n",question);
    fflush(stdout);
    while(1){
        input = get_ok_char();
        if(input == C_YES){
            return RES_YES;
        }
        if(input == C_NO){
            return RES_NO;
        }
        if(--maxtries == 0){
            return RES_OUTTIME;
        }
    }
}

int get_ok_char(){
    int c;
    while(( c = getchar() ) != EOF && strchr(OK_CHARS,c) == NULL);
    return c;
}
