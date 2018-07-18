# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/stat.h>
# include "stat_check.h"

# define USAGE_INFO "usage: %s source_dir target_dir\n"
void show_usage(const char* pro_name,FILE*stream=stderr);
void check_permission(const char*src,const int,const char* dst,const int);
void copy_dir(const char* src,const char* dst);
void copy_file(const char* src,const char* dst);

int main(int argc,char** argv){
    if(argc != 3){
        show_usage(argv[0]);
        return -1;
    }
    int src_stat = 0,dst_stat = 0;

    check_stat(argv[1],src_stat);
    check_stat(argv[2],dst_stat);

    check_permission(argv[1],,)

    if(is_dir(argv[1])){
        copy_dir(argv[1],argv[2]);
    }else{
        copy_file(argv[1],argv[2]);
    }
    return 0;
}

void show_usage(const char* pro_name,FILE*stream){
    fprintf(stream,USAGE_INFO,pro_name);
}


void check_permission(const char*src_path,const int src_stat,const char* dst_path,const int dst_stat){
   if()
}
