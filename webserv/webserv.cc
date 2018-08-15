# include <stdio.h>
# include <sys/stat.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <string.h>
# include <sys/socket.h>
# include "socklib.h"

# define EXESUFFIX "cgi"
# define DEBUG 0
# define RELEASE 1
# define RUNTYPE DEBUG

void read_til_crnl(FILE*);

void process_rq(const char*,int);

void header(FILE*,const char*);

void cannot_do(int);

void do_404(const char*,int);

int isadir(const char*);

int not_exist(const char*);

void do_ls(const char*,int);

const char* file_type(const char*);

int ends_in_cgi(const char*);

void do_exec(const char*,int);

void do_cat(const char*,int);

int main(int ac,char** av){
    int sock,fd;
    FILE *fpin;
    char request[BUFSIZ];

    if( ac == 1 ){
        fprintf(stderr,"usage: ws portnum");
        exit(1);
    }
    sock = make_server_socket(atoi(av[1]));
    if( sock == -1 )exit(2);

    while(1){
        fd = accept( sock, NULL, NULL );
        fpin = fdopen(fd, "r" );

        /*
         * read request
         */
        fgets(request,BUFSIZ,fpin);
        printf("got a call: request = %s",request);
        read_til_crnl(fpin);

        /*
         * do what client asks
         */
        process_rq(request,fd);
        fclose(fpin);
    }
}

void read_til_crnl(FILE* fp){
    char buf[BUFSIZ];
    while( fgets(buf,BUFSIZ,fp) != NULL && strcmp(buf,"\r\n") != 0 );
}

void process_rq( const char* rq,int fd ){
    char cmd[BUFSIZ],arg[BUFSIZ];

    /*
     * create a new process and return if not the child
     */
    if(fork() != 0){
        return;
    }

    strcpy(arg,".");
    if( sscanf(rq,"%s%s",cmd,arg+1) != 2 ){
        return;
    }

    if( strcmp(cmd,"GET") != 0 ){
        cannot_do(fd);
    }else if(not_exist( arg )){
        do_404(arg,fd);
    }else if( isadir(arg) ){
        do_ls(arg,fd);
    }else if( ends_in_cgi(arg) ){
        do_exec( arg,fd );
    }else{
        do_cat( arg,fd );
    }
}

void header(FILE* fp,const char* content_type){
    fprintf(fp,"HTTP/1.0 200 OK\r\n");
    if( content_type ){
        fprintf(fp,"Content-type: %s\r\n",content_type);
    }
}

void cannot_do(int fd){
    FILE* fp = fdopen(fd,"w");

    fprintf(fp,"HTTP/1.0 501 Not Implemented\r\n");
    fprintf(fp,"Content-type: text/plain\r\n");
    fprintf(fp,"\r\n");

    fprintf(fp,"That command is not yet implemented\r\n");
    fclose(fp);
}

void do_404(const char *item, int fd){
    FILE* fp = fdopen(fd,"w");

    fprintf(fp, "HTTP/1.0 404 Not Found\r\n");
    fprintf(fp, "Content-type: text/plain\r\n");
    fprintf(fp, "\r\n");

    fprintf(fp,"The item you requested: %s\r\nis not found\r\n",item);
    fclose(fp);
}

int isadir(const char* f){
    struct stat info;
    return (stat(f, &info) != -1 && S_ISDIR(info.st_mode));
}

int not_exist(const char* f){
    struct stat info;
    return ( stat(f, &info) == -1 );
}

void do_ls(const char* dir,int fd){
    FILE* fp;

    fp = fdopen(fd,"w");
    header(fp,"text/plain");
    fprintf(fp,"\r\n");
    fflush(fp);

    dup2(fd,STDOUT_FILENO);
    dup2(fd,STDERR_FILENO);
    close(fd);
    execlp("ls","ls","-l",dir,NULL);
    perror(dir);
    exit(1);
}

const char* file_type(const char* f){
    char *cp;
    if ((cp = strrchr(f,'.'))!= NULL ){
        return cp+1;
    }
    return "";
}

int ends_in_cgi(const char* f){
    return ( strcmp( file_type(f), EXESUFFIX) == 0 );
}

void do_exec(const char* prog,int fd){
#if RUNTYPE == DEBUG
    printf("do exec: %s\n",prog);
#endif
    FILE* fp;

    fp = fdopen(fd,"w");
    header(fp,NULL);
    fflush(fp);
    dup2(fd,STDOUT_FILENO);
    dup2(fd,STDERR_FILENO);
    close(fd);
    execl(prog,prog,NULL);
    perror(prog);
}

void do_cat(const char *f, int fd){
    const char *extension = file_type(f);
    char *content   = strdup("text/plain");
    FILE *fpsock, *fpfile;
    int c;

    if ( strcmp(extension,"html") == 0 ){
        free(content);
        content = strdup("text/html");
    }else if( strcmp(extension, "gif") == 0 ){
        free(content);
        content = strdup("image/gif");
    }else if( strcmp(extension,"jpg") == 0 ||
            strcmp(extension,"jpeg") == 0){
        free(content);
        content = strdup("image/jpeg");
    }
#if RUNTYPE == DEBUG
    printf("do cat: %s\n",f);
    printf("extension: %s\n",extension);
    printf("content: %s\n",content);
#endif

    fpsock = fdopen(fd,"w");
    fpfile = fopen(f,"r");
    if( fpsock != NULL && fpfile != NULL ){
        header( fpsock, content );
        fprintf( fpsock, "\r\n" );
        while( (c = getc(fpfile)) != EOF){
            putc(c, fpsock);
        }
        fclose(fpfile);
        fclose(fpsock);
    }
    exit(0);
}
