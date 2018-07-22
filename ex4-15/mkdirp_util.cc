# include "mkdirp_util.h"
# include "umask.h"
# include <string.h>
# include <unistd.h>
# include "error_process.h"

void smkdir(const char* path,mode_t mode);
void change_dir(const char*path);

void create_dir(const char* path,mode_t mode,bool has_intermediate){
    char* ap;
    char* t_path = strdup(path);
    if(!has_intermediate){
        smkdir(path,mode);
    }else{
        int chtimes = 0;
        while((ap = strsep(&t_path,"/"))!=NULL){
            char* buf;
            if(ap[0] == '\0'){
                buf = strdup("/");
            }else{
                buf = ap;
            }
            if(access(buf,F_OK) != 0){
                smkdir(buf,mode);
            }
            change_dir(buf);
            ++chtimes;
        }
        while(chtimes--){
            change_dir("..");
        }
    }
}

void create_dir(const char* path,bool has_intermediate){
    create_dir(path,~getumask(),has_intermediate);
}

void smkdir(const char* path,mode_t mode){
    if(mkdir(path,mode) == -1){
        oops("Create directory failed ",path);
    }
}

void change_dir(const char* path){
    if(chdir(path) == -1){
        oops("Change directory failed ",path);
    }
}
