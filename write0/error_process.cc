# include "error_process.h"

void oops(const char * s1,const char * s2){
    fprintf(stderr,"Error: %s",s1);
    perror(s2);
    exit(1);
}
