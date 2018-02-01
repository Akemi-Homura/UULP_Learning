# include <stdio.h>
# include <utmpx.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>
#define SHOWHOST

void show_info(utmpx * record);
void show_host(char* host);
void show_time(timeval dis_time);

int main(){
    utmpx* current_record;
    while((current_record = getutxent()) != NULL){
        show_info(current_record);
    }
    endutxent();
    return 0;
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
