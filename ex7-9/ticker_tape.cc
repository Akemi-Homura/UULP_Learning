# include "display_util.h"
# include "para_handler.h"
# include "screensz.h"

int main(int argc,char** argv){
    char* filepath;
    int speed,row,col;

    para_handler(argc,argv,filepath,speed);
    get_winsize(row,col);
    display(filepath,row,col,speed);
    return 0;
}
