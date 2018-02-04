# include <stdio.h>
# include <utmpx.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>
# include <sys/types.h>
# include <pwd.h>
# include <uuid/uuid.h>
# define SHOWHOST
# define AM "am"
# define I "i"

void show_info(utmpx * record);
void show_host(char* host);
void show_time(timeval dis_time);
void show_all_users();
void usage_error();
void show_real_user_name();

int main(int argc,char *argv[]){
    if(argc == 1){
        show_all_users();
    }else if(argc == 3){
        if(!(strcmp(argv[1],AM)==0 && strcmp(argv[2],I) == 0)){
            usage_error();
        }else{
            show_real_user_name();
        }
    }else{
        usage_error();
    }
    return 0;
}

void show_real_user_name(){
    int current_uid = getuid();
    passwd* real_passwd = getpwuid(current_uid);
    printf("%s\n",real_passwd->pw_name);
}

void usage_error(){
    fprintf(stderr,"who: illegal option -- -\n");
    fprintf(stderr,"usage:\nwho\t- display who is logged in\n");
    fprintf(stderr,"who am i\t- return the invokder's real user name\n");
}

void show_all_users(){
    utmpx* current_record;
    while((current_record = getutxent()) != NULL){
        show_info(current_record);
    }
    endutxent();
}

void show_info(utmpx * record){
    if(record->ut_type != USER_PROCESS){
        return;
    }
    printf("%-8.8s",record->ut_user);
    printf(" ");
    printf("%-8.8s",record->ut_line);
    printf(" ");
    show_time(record->ut_tv);
    printf(" ");
#ifdef SHOWHOST
    show_host(record->ut_host);
#endif
    printf("\n");
}

void show_host(char* host_name){
    if(strlen(host_name) != 0){
        printf("(%s)",host_name);
    }
}

void show_time(timeval dis_time){
    char *cp = ctime(&dis_time.tv_sec);
    printf("%12.12s",cp+4);
}
