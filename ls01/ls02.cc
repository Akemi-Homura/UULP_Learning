# include <stdio.h>
# include <dirent.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# define M_ALL 1
# define M_DEFAULT 0
# define ARGU_ALL "a"
# define USAGE_INFO "ls01 [-a] [file ...]\n"
# define ILLEGAL_OP_INFO "ls01: illegal option -- %s\n"
# define FILE_NOT_EXIST_MSG "ls01: %s: No such file or directory\n"

# define DEBUG 0
# define RELEASE 1
# define RUN_TYPE RELEASE

void do_ls(const char*);
void display(const char*);
void process_argv(const char*);
void process_option(const char*);
void show_usage(FILE*stream=stderr);
void illegal_option(const char*);
bool is_file_exits(const char*);

int mode = M_DEFAULT;
bool has_exectute = false;

int main(int argc,char * argv[]){
    if(argc == 1){
        do_ls(".");
    }else{
        for(int i=1;i<argc;i++){
            process_argv(argv[i]);
        }
#if RUN_TYPE == DEBUG
        printf("process argvs finished!\n");
#endif
        if(!has_exectute){
            do_ls(".");
        }
    }
    return 0;
}

void process_argv(const char* msg){
#if RUN_TYPE == DEBUG
    printf("processing argv: %s\n",msg);
#endif
    if(msg[0] == '-' && strlen(msg) > 1){
        process_option(msg+1);
    }else{
        do_ls(msg);
    }
}

void process_option(const char* op){
#if RUN_TYPE == DEBUG
    printf("Processing option: %s\n",op);
#endif
    if(strcmp(op,ARGU_ALL) == 0){
#if RUN_TYPE == DEBUG
        printf("Mode changing\n");
#endif
        mode = M_ALL;
    }else{
        fprintf(stderr,ILLEGAL_OP_INFO,op);
        show_usage();
        exit(1);
    }
#if RUN_TYPE == DEBUG
    printf("Process option: %s finished.\n",op);
#endif
}

void show_usage(FILE* stream){
    fprintf(stream,USAGE_INFO);
}

void do_ls(const char * path){
    has_exectute = true;
    if(!is_file_exits(path)){
        fprintf(stderr,FILE_NOT_EXIST_MSG,path);
        exit(1);
    }
    DIR* dir_ptr;
    dirent* direntp;
    if((dir_ptr = opendir(path)) == NULL){
        fprintf(stderr,"ls01: cannot open %s\n",path);
    }else{
        while((direntp = readdir(dir_ptr)) != NULL){
            display(direntp->d_name);
        }
        closedir(dir_ptr);
    }
}

void display(const char* msg){
    if(mode == M_ALL || msg[0] != '.'){
        printf("%s\n",msg);
    }
}

bool is_file_exits(const char* path){
    return access(path,F_OK) == 0;
}
