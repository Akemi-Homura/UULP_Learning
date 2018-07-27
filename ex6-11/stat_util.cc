# include "stat_util.h"
# include <stdlib.h>
# include <stdio.h>

# define oops(s,x) {perror(s); exit(x);}

struct stat get_file_status(int fd){
    struct stat res;
    if(fstat(fd,&res) == -1){
        oops("fstat",1);
    }
    return res;
}

off_t get_file_size(int fd){
    return get_file_size(get_file_status(fd));
}

off_t get_file_size(const struct stat info){
    return info.st_size;
}
