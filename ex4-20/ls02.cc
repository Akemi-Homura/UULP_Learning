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
/* modes */
# define S_INO 16
# define S_U 8
# define S_ALL 04
# define S_DETAIL 02
# define S_DEFAULT 00

# define IS_U(MODE) ((MODE&S_U) == S_U)
# define S_IS_INO(mode) ((mode&S_INO) == S_INO)

# define ARGU_INO    'i'
# define ARGU_ALL    'a'
# define ARGU_DETAIL 'l'
# define ARGU_U      't'
# define USAGE_INFO "ls02 [-a] [file ...]\n"
# define ILLEGAL_OP_INFO "ls02: illegal option -- %s\n"
# define FILE_NOT_EXIST_MSG "ls02: %s: No such file or directory\n"
# define TIMEOFFSET 4

# define DEBUG 0
# define RELEASE 1
# define RUN_TYPE RELEASE

void do_ls(const char*);
void display(const char*,std::vector<dirent*>);
struct stat get_stat(const dirent*);
void process_argv(const char*);
void process_option(const char*);
void show_usage(FILE*stream=stderr);
void illegal_option(const char*);
void show_file_info(const char*,const struct stat*);
void dostat(const char*);
void merge_path(const char*,const char*,char*&);
bool is_file_exits(const char*);
bool name_cmp(const dirent* d1,const dirent* d2);
bool access_time_cmp(const dirent*,const dirent*);
void oops(const char*,const char*);
void mode_to_letters(mode_t,char *);
ino_t get_ino(const char* path);
char* uid_to_name(const uid_t);
char* gid_to_name(const gid_t);

static int mode = S_DEFAULT;
static bool has_exectute = false;

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
    int len = strlen(op);
    for(int i=0;i<len;i++){
        switch(op[i]){
            case ARGU_ALL:
                mode |= S_ALL;
                break;
            case ARGU_DETAIL:
                mode |= S_DETAIL;
                break;
            case ARGU_U:
                mode |= S_U;
                break;
            case ARGU_INO:
                mode |= S_INO;
                break;
            default:
                fprintf(stderr,"ls02: illegal option -- %c\n",op[i]);
                show_usage();
                exit(1);
        }
    }
#if RUN_TYPE == DEBUG
    printf("Process option: %s finished.\nmode: %d\n",op,mode);
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
        fprintf(stderr,"ls02: cannot open %s\n",path);
    }else{
        while((direntp = readdir(dir_ptr)) != NULL){
            if((mode & S_ALL) || direntp->d_name[0]!='.'){
                contents.push_back(direntp);
            }
        }
        display(path,contents);
        closedir(dir_ptr);
    }
}

void display(/*parent path*/const char* p_path,std::vector<dirent*> contents){
#if RUN_TYPE == DEBUG
    printf("Parent path: %s\n",p_path);
#endif
    if(IS_U(mode)){
        sort(contents.begin(),contents.end(),access_time_cmp);
    }else{
        sort(contents.begin(),contents.end(),name_cmp);
    }
#if RUN_TYPE == DEBUG
    printf("Sort complete\n");
#endif
    struct stat* file_info;
    if((file_info = (struct stat*)malloc(sizeof(struct stat))) == NULL){
        perror("malloc error\n");
        exit(1);
    }
    for(dirent* content : contents){
        char *path;
        merge_path(p_path,content->d_name,path);
        if(mode & S_INO){
            printf("%7lld ",get_ino(path));
        }
        if(!(mode & S_DETAIL)){
            printf("%s\n",content->d_name);
        }else if(mode & S_DETAIL){
#if RUN_TYPE == DEBUG
            printf("Merged path: %s\n",path);
#endif
            if(stat(path,file_info) == -1){
                oops("Get status failed! ",path);
            }
#if RUN_TYPE == DEBUG
            printf("Stat file status successful\n");
#endif
            show_file_info(content->d_name,file_info);
            free(path);
        }
    }
    free(file_info);
}

bool name_cmp(const dirent* d1,const dirent* d2){
    return strcmp(d1->d_name,d2->d_name) < 0;
}

bool access_time_cmp(const dirent* d1,const dirent* d2){
    struct stat s1_buf,s2_buf;
    if(stat(d1->d_name,&s1_buf) == -1){
        oops("Get status failed! ",d1->d_name);
    }
    if(stat(d2->d_name,&s2_buf) == -1){
        oops("Get status failed! ",d2->d_name);
    }
    return s1_buf.st_atime > s2_buf.st_atime;
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
    if(IS_U(mode)){
        printf("%.12s ",TIMEOFFSET + ctime(&record->st_atime));
    }else{
        printf("%.12s ",TIMEOFFSET + ctime(&record->st_mtime));
    }
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

void merge_path(const char*s1,const char*s2,char*& res){
    int len1 = strlen(s1), len2 = strlen(s2);
    int n_size = len1 + len2 + 2;
    if((res = (char*)malloc(n_size)) == NULL){
        perror("malloc error\n");
        exit(1);
    }
    memcpy(res,s1,len1);
    res[len1]='/';
    memcpy(res+len1+1,s2,len2);
    res[len1+len2+1] = '\0';
}

struct stat get_stat(const char* path){
    struct stat s_buf;
    if(stat(path,&s_buf) == -1){
        oops("Can't get status ",path);
    }
    return s_buf;
}

bool is_file_exits(const char* path){
    return access(path,F_OK) == 0;
}

ino_t get_ino(const char*path){
    struct stat s_buf = get_stat(path);
    return s_buf.st_ino;
}
