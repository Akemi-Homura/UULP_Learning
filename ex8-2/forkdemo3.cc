# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

int main(){
    for(int n=0;n<10;n++){
        printf("my pid = %d, n = %d\n",getpid(),n);
        sleep(1);
        if(fork()!=0){
            exit(0);
        }
    }
    return 0;
}
