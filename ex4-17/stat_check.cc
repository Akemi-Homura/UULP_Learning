# include "stat_check.h"

void check_stat(const char* path,int &res){
    res = 0;
    if(is_exist(path)){
        res |= STAT_F;
    }
    if(is_dir(path)){
        res |= STAT_DIR;
    }

    if(is_readable(path)){
        res |= STAT_R;
    }
    if(is_writable(path)){
        res |= STAT_W;
    }
}

bool is_exist(const char* path){
    return access(path,F_OK) == 0;
}

bool is_dir(const char* path){
    struct stat s_buf;
    stat(path,&s_buf);
    return S_ISDIR(s_buf.st_mode);
}

bool is_file(const char* path){
    struct stat s_buf;
    stat(path,&s_buf);
    return S_ISREG(s_buf.st_mode);
}

bool is_readable(const char* path){
    return access(path,R_OK) == 0;
}

bool is_writable(const char* path){
    return access(path,W_OK) == 0;
}
