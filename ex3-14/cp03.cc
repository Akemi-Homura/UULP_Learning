# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/stat.h>
# include "stat_check.h"
# include "error_process.h"
# include "copy_util.h"

# define USAGE_INFO "usage: %s source_dir target_dir\n"
void show_usage(const char* pro_name,FILE*stream=stderr);
void check_permission(const char*,const int,const char*,const int);

int main(int argc,char** argv){
    if(argc != 3){
        show_usage(argv[0]);
        return -1;
    }

    if(is_dir(argv[1])){
        if(is_exist(argv[2])){
            if(is_dir(argv[2])){
                copy_dir(argv[1],merge_path(argv[2],argv[1]));
            }else{
                fprintf(stderr,"%s: %s: not a directory",argv[0],argv[2]);
            }
        }else{
            copy_dir(argv[1],argv[2]);
        }
    }else{
        copy_file(argv[1],argv[2]);
    }
    return 0;
}

void show_usage(const char* pro_name,FILE*stream){
    fprintf(stream,USAGE_INFO,pro_name);
}

