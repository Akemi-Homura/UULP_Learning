# include "copy_util.h"
# include <stdio.h>
# include "error_process.h"
# include <dirent.h>
# include <string.h>
# include "stat_check.h"
# include <sys/stat.h>

# define SIZE 1024
# define DEFAULT_MODE 0755

void copy_file(const char*src,const char* dst){
    FILE *in,*out;
    if((in = fopen(src,"r")) == NULL){
        oops("Can't open file ",src);
    }
    if((out = fopen(dst,"w")) == NULL){
        oops("Can't open file ",dst);
    }

    char buf[SIZE+1];

    while(fgets(buf,SIZE,in) != NULL){
        if(fputs(buf,out) == EOF){
            oops("Write file failed ",dst);
        }
    }
    if(feof(in) == 0){
        oops("Read file failed ",src);
    }

    fclose(in);
    fclose(out);
}

void copy_dir(const char* src,const char* dst){
    if(mkdir(dst,DEFAULT_MODE) == -1){
        oops("Can't create directory ",dst);
    }
    DIR* dir_ptr = NULL;
    if((dir_ptr = opendir(src)) == NULL){
        oops("Can't open directory ",src);
    }
    struct dirent* dp;
    while((dp = readdir(dir_ptr)) != NULL){
        if(strcmp(dp->d_name,".") == 0 || strcmp(dp->d_name,"..") ==0){
            continue;
        }
        char* src_path = merge_path(src,dp->d_name);
        char* dst_path = merge_path(dst,dp->d_name);
        if(is_dir(src_path)){
            copy_dir(src_path,dst_path);
        }else{
            copy_file(src_path,dst_path);
        }
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
