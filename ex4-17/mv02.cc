# include <stdio.h>
# include "stat_check.h"
# include "string.h"
# include "error_process.h"

void show_usage(const char* pro_name);
void move_file(const char* src,const char* dst);
char* merge_path(const char* ,const char*);

int main(int argc,char** argv){
    if(argc != 3){
        show_usage(argv[0]);
        exit(1);
    }
    if(!is_file(argv[1])){
        fprintf(stderr,"%s is not a file!\n",argv[1]);
        exit(1);
    }
    char *dst_path = argv[2];
    if(is_dir(argv[2])){
        dst_path = merge_path(argv[2],argv[1]);
    }
    move_file(argv[1],dst_path);
}

void move_file(const char* src,const char* dst){
    if(is_exist(dst)){
        if(unlink(dst) == -1){
            oops("Unlink file failed ",src);
        }
    }
    if(link(src,dst) == -1){
        oops("Create link failed ",dst);
    }
    if(unlink(src) == -1){
        oops("Unlink file failed ",src);
    }
}

char* merge_path(const char*s1,const char*s2){
    int len1 = strlen(s1), len2 = strlen(s2);
    int n_size = len1 + len2 + 2;
    char* res;
    if((res = (char*)malloc(n_size)) == NULL){
        perror("malloc error\n");
        exit(1);
    }
    memcpy(res,s1,len1);
    res[len1]='/';
    memcpy(res+len1+1,s2,len2);
    res[len1+len2+1] = '\0';
    return res;
}

void show_usage(const char* pro_name){
    fprintf(stderr,"usage: %s source target\n",pro_name);
}
