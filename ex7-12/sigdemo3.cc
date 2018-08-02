# include <stdio.h>
# include <signal.h>
# include <unistd.h>
# include <string.h>

# define INPUTLEN 100

int main(){
    void ctrl_cq_handler(int);
    char input[INPUTLEN];
    int nchars;

    signal( SIGINT, ctrl_cq_handler );
    signal( SIGQUIT, ctrl_cq_handler );

    do{
        printf("\nType a message\n");
        nchars = read(0, input, (INPUTLEN-1));
        if( nchars == -1){
            perror("read returned an error");
        }else{
            input[nchars] = '\0';
            printf("You typed: %s",input);
        }
    }while(strncmp( input, "quit", 4) != 0);
}

void ctrl_cq_handler(int signum){
    if(signum == SIGINT){
        printf(" Received signal %d.. waiting\n",signum);
        sleep(2);
        printf(" Leaving inthandler\n");
    }else if(signum == SIGQUIT){
        printf(" Received signal %d.. waiting\n",signum);
        sleep(3);
        printf(" Leaving quithandler\n");
    }
}
