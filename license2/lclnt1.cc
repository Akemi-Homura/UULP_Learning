# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "lclnt_funcs1.h"

# define RELEASE 0
# define DEBUG   1
# define RUNTYPE DEBUG

void do_regular_work();

int main(){
    setup();
    if(get_ticket()!=0){
#if RUNTYPE == RELEASE
        printf("Get ticket failed\n");
#endif
        exit(0);
    }

    do_regular_work();

    release_ticket();

    shut_down();

    return 0;
}

void do_regular_work(){
    printf("SuperSleep version 1.0 Running-Licensed Software\n");
    sleep(3);
    if(validate_ticket() != 0){
        exit(1);
    }
    sleep(3);
}
