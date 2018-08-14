# include <stdio.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>

# define oops(m,x) {perror(m); exit(x);}

void be_dc(int fd);
void fatal(const char*);
void be_bc(int fd);

# define DCEND 0
# define BCEND 1

int main(){
    int pid,apipe[2];
    if(socketpair(AF_UNIX, SOCK_STREAM, PF_UNSPEC, apipe) == -1){
        oops("socketpair",1);
    }

    if( (pid = fork()) == -1 ){
        oops("cannot fork",2);
    }

    if( pid == 0 ){
        close(apipe[BCEND]);
        be_dc(apipe[DCEND]);
    }else{
        close(apipe[DCEND]);
        be_bc(apipe[BCEND]);
        wait(NULL);
    }
    return 0;
}

void be_dc(int fd){
    // redirect stdin
    if(dup2(fd,STDIN_FILENO) == -1){
        oops("dc: cannot redirect stdin",3);
    }

    // redirect stdout
    if( dup2(fd,STDOUT_FILENO) == -1){
        oops("dc: cannot redirect stdout",4);
    }
    close(fd);

    // - means stdin
    execlp("dc","dc","-",NULL);
    oops("Cannot run dc",5);
}

void be_bc(int fd){
    int num1,num2;
    char operation[BUFSIZ],message[BUFSIZ];
    FILE *fp;

    fp = fdopen(fd,"a");
    if(fp == NULL || fp == NULL){
        fatal("Error convering pipes to streams");
    }

    while(printf("tinybc: "),fgets(message,BUFSIZ,stdin) != NULL){
        if(sscanf(message, "%d%[-+*/^]%d",&num1,operation,&num2) != 3){
            printf("syntax error\n");
            continue;
        }

        if(fprintf(fp,"%d\n%d\n%c\np\n",num1,num2,
                    *operation) == EOF){
            fatal("Error writing");
        }
        fflush(fp);
        if( fgets(message, BUFSIZ, fp) == NULL ){
            break;
        }
        printf("%d %c %d = %s",num1,*operation,num2,message);
    }
    fclose(fp);
}

void fatal(const char* msg){
    fprintf(stderr,"Error: %s\n",msg);
    exit(1);
}
