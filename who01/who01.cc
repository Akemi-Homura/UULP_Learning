# include <stdio.h>
# include <utmpx.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
#define SHOWHOST

void show_info(utmpx * record);

int main(){
    utmpx current_record;
    int reclen = sizeof(utmpx);
    int utmpx_fd;
    if((utmpx_fd = open(_PATH_UTMPX,O_RDONLY)) == -1){
        fprintf(stderr,"open %s file failed\n",_PATH_UTMPX);
        exit(1);
    }
    while(read(utmpx_fd,&current_record,reclen) == reclen){
        show_info(&current_record);
    }
    return 0;
}

void show_info(utmpx * record){
    printf("%-8.8s",record->ut_user);
    printf(" ");
    printf("%-8.8s",record->ut_line);
    printf(" ");
    printf("%10d",record->ut_tv.tv_usec);
    printf(" ");
#ifdef SHOWHOST
    printf("(%s)",record->ut_host);
#endif
    printf("\n");
}
