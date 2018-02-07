# include <stdio.h>
# include <dirent.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <vector>
# include <string>
# include <algorithm>
# include <sys/stat.h>
# include <time.h>
# include <sys/types.h>
# include <pwd.h>
# include <uuid/uuid.h>
# include <grp.h>
# define M_ALL 1
# define M_DEFAULT 0
# define M_DETAIL 2
# define ARGU_ALL "a"
# define ARGU_DETAIL "l"
# define USAGE_INFO "ls01 [-a] [file ...]\n"
# define ILLEGAL_OP_INFO "ls01: illegal option -- %s\n"
# define FILE_NOT_EXIST_MSG "ls01: %s: No such file or directory\n"
# define TIMEOFFSET 4

# define DEBUG 0
# define RELEASE 1
# define RUN_TYPE RELEASE

void do_ls(const char*);
void display(const char*,std::vector<dirent*>);
void process_argv(const char*);
void process_option(const char*);
void show_usage(FILE*stream=stderr);
void illegal_option(const char*);
void show_file_info(const char*,const struct stat*);
void dostat(const char*);
char* merge_str(const char*,const char*);
bool is_file_exits(const char*);
bool dirent_cmp(const dirent* d1,const dirent* d2);
void oops(const char*,const char*);
void mode_to_letters(mode_t,char *);
char* uid_to_name(const uid_t);
char* gid_to_name(const gid_t);

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
    }else if(strcmp(op,ARGU_DETAIL) == 0){
        mode = M_DETAIL;
    }else {
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
    std::vector<dirent*> contents;
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
            contents.push_back(direntp);
        }
        display(path,contents);
        closedir(dir_ptr);
    }
}

void display(/*parent path*/const char* p_path,std::vector<dirent*> contents){
#if RUN_TYPE == DEBUG
    printf("Parent path: %s\n",p_path);
#endif
    sort(contents.begin(),contents.end(),dirent_cmp);
#if RUN_TYPE == DEBUG
    printf("Sort complete\n");
#endif
    for(dirent* content : contents){
        if(mode == M_ALL || (mode == M_DEFAULT && content->d_name[0] != '.')){
            printf("%s\n",content->d_name);
        }else if(mode == M_DETAIL){
            char *path = merge_str(merge_str(p_path,"/"),content->d_name);
#if RUN_TYPE == DEBUG
            printf("Merged path: %s\n",path);
#endif
            struct stat* file_info = (struct stat*)malloc(sizeof(struct stat));
            if(stat(path,file_info) == -1){
                oops("Get status failed! ",path);
            }
#if RUN_TYPE == DEBUG
            printf("Stat file status successful\n");
#endif
            show_file_info(content->d_name,file_info);
        }
    }
}

bool dirent_cmp(const dirent* d1,const dirent* d2){
    return strcmp(d1->d_name,d2->d_name) < 0;
}

void show_file_info(const char*filename,const struct stat* record){
    char modestr[11];
    mode_to_letters(record->st_mode,modestr);
    modestr[10] = '\0';
#if RUN_TYPE == DEBUG
    printf("Mode to letters successful\n");
#endif

    printf("%s",modestr);
    printf("%4d ",(int)record->st_nlink);
    printf("%-8s ",uid_to_name(record->st_uid));
    printf("%-8s ",gid_to_name(record->st_gid));
    printf("%8ld ",(long)record->st_size);
    printf("%.12s ",TIMEOFFSET + ctime(&record->st_mtime));
    printf("%s\n",filename);
}

char* uid_to_name(const uid_t uid){
    static char str[10];
    passwd* record;
    if((record = getpwuid(uid)) == NULL){
        sprintf(str,"%d",uid);
        return str;
    }else{
        return record->pw_name;
    }
}

char* gid_to_name(const gid_t gid){
    static char str[10];
    group* record;
    if((record = getgrgid(gid)) == NULL){
        sprintf(str,"%d",gid);
        return str;
    }else{
        return record->gr_name;
    }
}

void mode_to_letters(mode_t mode,char* res){
    strcpy(res,"----------");

    /*file type*/
    if(S_ISDIR(mode)) res[0]='d';
    if(S_ISCHR(mode)) res[0]='c';
    if(S_ISBLK(mode)) res[0]='b';

    /*permission for owner*/
    if(mode & S_IRUSR) res[1] = 'r';
    if(mode & S_IWUSR) res[2] = 'w';
    if(mode & S_IXUSR) res[3] = 'x';

    /*permission for group members*/
    if(mode & S_IRGRP) res[4] = 'r';
    if(mode & S_IWGRP) res[5] = 'w';
    if(mode & S_IXGRP) res[6] = 'x';

    /*permission for others*/
    if(mode & S_IROTH) res[7] = 'r';
    if(mode & S_IWOTH) res[8] = 'w';
    if(mode & S_IXOTH) res[9] = 'x';
}

void oops(const char* s1,const char* s2){
    fprintf(stderr,"Error: %s ",s1);
    perror(s2);
    exit(1);
}

char * merge_str(const char*s1,const char*s2){
    int len1 = strlen(s1), len2 = strlen(s2);
    int n_size = len1 + len2 + 1;
    static char * res = (char*)malloc(n_size);
    memcpy(res,s1,len1);
    memcpy(res+len1,s2,len2);
    res[len1+len2] = '\0';
    return res;
}

bool is_file_exits(const char* path){
    return access(path,F_OK) == 0;
}
