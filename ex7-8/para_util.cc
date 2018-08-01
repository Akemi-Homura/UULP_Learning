# include <string.h>
# include "para_util.h"
# include <stdlib.h>
# define MESSAGE "hello world"

void para_handler(int argc,char** argv,int& len,char*&res){
    if(argc > 1){
        len = argc - 2;
        for(int i=0;i<argc;i++){
            len += strlen(argv[0]);
        }
        res = (char*)malloc(len);

        for(int i=1,tot_len = 0;i<argc;i++){
            strcat(res,argv[i]);
            int temp_len = strlen(argv[i]);
            res[tot_len + temp_len ] = ' ';
            tot_len += temp_len + 1;
        }
    }else{
        res = strdup(MESSAGE);
        len = strlen(res);
    }
}
