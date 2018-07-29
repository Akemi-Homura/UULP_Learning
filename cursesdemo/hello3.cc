# include <stdio.h>
# include <curses.h>
# include <unistd.h>

int main(){
    initscr();
    clear();

    for(int i=0;i<LINES;i++){
        if(i&1){
            standout();
        }
        addstr("Hello world");
        if(i&1){
            standend();
        }
        sleep(1);
        refresh();
    }

    endwin();
    return 0;
}
