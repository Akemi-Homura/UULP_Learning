# include <stdio.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

int main(){
    int pid;

    printf("About to run who into a file\n");

    if( (pid = fork()) == -1){
        perror("fork"); exit(1);
    }

    if( pid == 0 ){
        close(1);
        open("userlist",O_WRONLY | O_CREAT | O_APPEND,0644);
        execlp("who","who",NULL);
        perror("execlp");
        exit(1);
    }

    if(pid != 0){
        wait(NULL);
        printf("Done running who. results in userlist\n");
        return 0;
    }
}
