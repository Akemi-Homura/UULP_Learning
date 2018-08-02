# include "para_handler.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# define INVALID_OPTION_MSG(pro,op) {fprintf(stderr,"%s: invalid option -- %c\n",pro,op);}
# define SHOW_USAGE(pro) {fprintf(stderr,"usage: %s [-s speed] file\n",pro);}
# define NO_DEST_FILE(pro) {fprintf(stderr,"%s: missing destination file\n",pro);}
# define DUP_SPEED_OP(pro) {fprintf(stderr,"%s: duplicate define speed\n",pro);}
# define PRONAME "ticker"

# define DFLSPEED 5
# define OP_SPEED 's'

void para_handler(int argc,char** argv,char*& filepath,int& speed){
    bool get_file_flag = false;
    bool get_speed_flag = false;
    speed = DFLSPEED;
    for(int i=1;i<argc;i++){
        if(strlen(argv[i]) > 1 && argv[i][0] == '-'){
            if(argv[i][1] != OP_SPEED){
                INVALID_OPTION_MSG(PRONAME,argv[i][1]);
                exit(1);
            }else{
                if(get_speed_flag){
                    DUP_SPEED_OP(PRONAME);
                    exit(1);
                }
                speed = atoi(argv[++i]);
                get_speed_flag = true;
            }
        }else{
            get_file_flag = true;
            filepath = argv[i];
            break;
        }
    }
    if(!get_file_flag){
        NO_DEST_FILE(PRONAME);
        SHOW_USAGE(PRONAME);
        exit(1);
    }
}
