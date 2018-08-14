# include <stdio.h>
# include <strings.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>

# define oops(m,x) {perror(m); exit(x);}
# define DELIM  "\n"
# define DEBUG 0
# define RELEASE 1
# define RUNTYPE RELEASE

void be_dc(int in[2],int out[2]);
void fatal(const char*);
void be_bc(int in[2],int out[2]);
void do_dc(char* message,FILE* fpin,FILE* fpout);

int main(){
    int pid,todc[2],fromdc[2];

    if( pipe(todc) == -1 || pipe(fromdc) == -1 ){
        oops("pipe failed",1);
    }

    if( (pid = fork()) == -1 ){
        oops("cannot fork",2);
    }

    if( pid == 0 ){
        be_dc(todc,fromdc);
    }else{
        be_bc(todc,fromdc);
        wait(NULL);
    }
    return 0;
}

void be_dc(int in[2],int out[2]){
    // redirect stdin
    if(dup2(in[0],STDIN_FILENO) == -1){
        oops("dc: cannot redirect stdin",3);
    }
    close(in[0]);
    close(in[1]);

    // redirect stdout
    if( dup2(out[1],STDOUT_FILENO) == -1){
        oops("dc: cannot redirect stdout",4);
    }
    close(out[1]);
    close(out[0]);

    // - means stdin
    execlp("dc","dc","-",NULL);
    oops("Cannot run dc",5);
}

void be_bc(int todc[2],int fromdc[2]){
    FILE *fpout, *fpin;

    close(todc[0]);
    close(fromdc[1]);

    fpout = fdopen(todc[1],"w");
    fpin  = fdopen(fromdc[0],"r");
    if(fpout == NULL || fpin == NULL){
        fatal("Error convering pipes to streams");
    }

    char tmp[BUFSIZ];
    while(fgets(tmp,BUFSIZ,stdin) != NULL){
#if RUNTYPE == DEBUG
        printf("tmp=%s\n",tmp);
#endif
        printf("tinybc: ");
        int len = strlen(tmp);
        for(int st=0,delim=0;delim < len;delim++){
            if(tmp[delim] == '\n'){
#if RUNTYPE == DEBUG
                printf("delim=%d\n",delim);
#endif
                tmp[delim] = '\0';
                do_dc(tmp+st,fpin,fpout);
                st = delim + 1;
            }
        }
    }
    fclose(fpout);
    fclose(fpin);
}

void fatal(const char* msg){
    fprintf(stderr,"Error: %s\n",msg);
    exit(1);
}

void do_dc(char* message,FILE* fpin,FILE* fpout){
#if RUNTYPE == DEBUG
    printf("%s\n",message);
    printf("len=%ld\n",strlen(message));
#endif
    int num1,num2;
    char operation[BUFSIZ];
    if(sscanf(message, "%d%[-+*/^]%d",&num1,operation,&num2) != 3){
        printf("syntax error\n");
        return;
    }

    if(fprintf(fpout,"%d\n%d\n%c\np\n",num1,num2,
                *operation) == EOF){
        fatal("Error writing");
    }
    fflush(fpout);
    if( fgets(message, BUFSIZ, fpin) == NULL ){
        exit(0);
    }
    printf("%d %c %d = %s",num1,*operation,num2,message);
}
