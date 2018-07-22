# include <stdio.h>
# include "mkdirp_util.h"
# include <stdlib.h>
# include <string.h>

#define OP_P "-p"
#define S_P 01
#define S_IS_P(mode) ((mode&S_P) == S_P)

void show_usage(const char* pro_name);
void illegal_option(const char* pro_name,const char op);

int main(int argc,char** argv){
    int st = 1;
    int mode = 0;
    if(argc == 1){
        show_usage(argv[0]);
        exit(1);
    }
    if(argv[1][0] == '-' && strlen(argv[1]) > 1){
        if(strcmp(argv[1],OP_P) == 0){
            st = 2;
            mode |= S_P;
        }else{
            illegal_option(argv[0],argv[1][1]);
        }
    }
    for(int i=st;i<argc;i++){
        create_dir(argv[i],S_IS_P(mode));
    }
    return 0;
}

void show_usage(const char* pro_name){
    fprintf(stderr,"usage: %s [-p] directory ...\n",pro_name);
}

void illegal_option(const char* pro_name,const char op){
    fprintf(stderr,"%s: illegal_option -- %c\n",pro_name,op);
    show_usage(pro_name);
}
