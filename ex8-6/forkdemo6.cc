# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

int main(){
    if(fork() != 0){
        exit(0);
    }

    for(int i=1;i<=10;i++){
        printf("still here..\n");
        sleep(i);
    }
    return 0;
}
