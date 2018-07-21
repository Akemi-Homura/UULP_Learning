# include "inode_util.h"

ino_t get_ino(const char* path){
    struct stat s_buf;
    if(stat(path,&s_buf) == -1){
        oops("Can't get file status ",path);
    }
    return s_buf.st_ino;
}
