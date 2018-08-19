# include "socklib.h"
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <string.h>
# include <sys/stat.h>
# include <unistd.h>
# include <dirent.h>
# include <time.h>

# define PRONAME "twebserv"

time_t  server_started;
int     server_bytes_sent;
int     server_requests;

void setup(pthread_attr_t* attrp);
void skip_rest_of_header(FILE*);
void process_rq(const char*,int);
void sanitize(char*);
int built_in(const char*arg,int);
int http_reply(int, FILE**,int,const char*,const char*,const char*);
void not_implemented(int);
void do_404(int);
void do_ls(const char*dir,int);
int isadir(const char*f);
int not_exist(const char*);
const char* file_type(const char*);
void do_cat(const char*f,int);

int main(int ac,char ** av){
    int     sock,fd;
    int     *fdptr;
    pthread_t worker;
    pthread_attr_t attr;

    void *handle_call(void*);

    if(ac == 1){
        fprintf(stderr,"usage: %s portnum\n",PRONAME);
        exit(1);
    }

    sock = make_server_socket(atoi(av[1]));
    if( sock == -1 ) {perror("making socket"); exit(2);}

    setup(&attr);

    /* main loop here: take call, handle call in the new thread */
    while(1){
        fd = accept(sock, NULL, NULL);
        server_requests++;
        fdptr = (int*)malloc(sizeof(int));
        *fdptr = fd;
        pthread_create(&worker, &attr, handle_call, fdptr);
    }
}

/*
 * initialize the status variables and
 * set the thread attribute to detached
 */
void setup(pthread_attr_t* attrp){
    pthread_attr_init(attrp);
    pthread_attr_setdetachstate(attrp, PTHREAD_CREATE_DETACHED);

    time(&server_started);
    server_requests   = 0;
    server_bytes_sent = 0;
}

void *handle_call(void* fdptr){
    FILE *fpin;
    char request[BUFSIZ];
    int fd;

    fd = *(int*)fdptr;
    free(fdptr);

    fpin = fdopen(fd,"r");
    fgets(request,BUFSIZ,fpin);
    printf("got a call on %d: request = %s",fd,request);
    skip_rest_of_header(fpin);

    process_rq(request,fd);

    fclose(fpin);
    return NULL;
}

void skip_rest_of_header(FILE* fp){
    char buf[BUFSIZ];
    memset(buf,0,sizeof(buf));
    while( fgets(buf, BUFSIZ, fp) != NULL && strcmp(buf,"\r\n") != 0);
}

/*
 * do what the request ask for and write reply to fd handles
 * request in a new process
 * rq is HTTP command: GET /foo/bar.html HTTP/1.0
 */
void process_rq(const char*rq,int fd){
    char cmd[BUFSIZ], arg[BUFSIZ];

    if ( sscanf(rq,"%s%s",cmd,arg) != 2 ){
        return;
    }
    sanitize(arg);
    printf("sanitized version is %s\n",arg);

    if( strcmp(cmd,"GET") != 0 ){
        not_implemented(fd);
    }else if ( built_in(arg,fd));
    else if(not_exist(arg)){
        do_404(fd);
    }else if( isadir(arg) ){
        do_ls(arg, fd);
    }else{
        do_cat(arg,fd);
    }
}

/*
 * make sure all paths are below the current directory
 */
void sanitize(char*str){
    char *src, *dest;
    src = dest = str;

    while(*src){
        if(strncmp(src,"/../",4) == 0){
            src += 3;
        }else if(strncmp(src,"//",2) == 0 ){
            src++;
        }else{
            *dest++ = *src++;
        }
    }

    *dest = '\0';
    if( *str == '/' ){
        strcpy(str,str+1);
    }

    if(str[0] == '\0' || strcmp(str,"./") == 0 || strcmp(str,"./..") == 0){
        strcpy(str,".");
    }
}

/*
 * handle built - in URLS here. Only one so far is "status"
 */
int built_in(const char* arg,int fd){
    FILE *fp;

    if(strcmp(arg,"status") != 0){
        return 0;
    }

    http_reply(fd, &fp, 200, "OK", "text/plain", NULL);

    fprintf(fp,"Server started: %s",ctime(&server_started));
    fprintf(fp,"Total requests: %d\n",server_requests);
    fprintf(fp,"Bytes sent out: %d\n",server_bytes_sent);
    fflush(fp);

    fclose(fp);
    return 1;
}

int http_reply(int fd,FILE **fpp,int code, const char*msg,const char* type,const char *content){
    FILE    *fp = fdopen(fd,"w");
    int bytes = 0;
    if( fp != NULL ){
        bytes = fprintf(fp,"HTTP/1.0 %d %s\r\n",code,msg);
        bytes += fprintf(fp,"Content-type: %s\r\n\r\n",type);
        if(content){
            bytes += fprintf(fp,"%s\r\n",content);
        }
    }

    fflush(fp);
    if(fpp){
        *fpp = fp;
    }else{
        fclose(fp);
    }
    return bytes;
}
/*
 * unimplemented HTTP command
 */
void not_implemented(int fd){
    http_reply(fd,NULL,501,"Not Implemented","text/plain",
            "That command is not implemented");
}

void do_404(int fd){
    http_reply(fd,NULL, 404, "Not Found","text/plain",
            "The you seek is not here");
}

int isadir(const char *f){
    struct stat info;
    return (stat(f,&info)!=-1 && S_ISDIR(info.st_mode));
}

int not_exist(const char*f){
    struct stat info;
    return (stat(f,&info) == -1);
}

void do_ls(const char*dir,int fd){
    DIR     *dirptr;
    struct dirent * direntp;
    FILE    *fp;
    int     bytes = 0;

    bytes = http_reply(fd,&fp, 200, "OK", "text/plain",NULL);
    bytes += fprintf(fp,"Listing of Diectory %s\n",dir);

    if( (dirptr = opendir(dir)) != NULL){
        while ( (direntp = readdir(dirptr) )){
            bytes += fprintf(fp,"%s\n",direntp->d_name);
        }
        closedir(dirptr);
    }
    fclose(fp);
    server_bytes_sent += bytes;
}

const char* file_type(const char*f){
    char *cp;
    if( (cp = strrchr(f,'.')) != NULL){
        return cp+1;
    }
    return " -";
}

void do_cat(const char*f,int fd){
    const char* extension = file_type(f);
    const char *type;
    FILE *fpsock, *fpfile;
    int c,bytes = 0;

    if( strcmp(extension,"html") == 0){
        type = "text/html";
    }else if( strcmp(extension, "gif") == 0){
        type = "image/gif";
    }else if( strcmp(extension,"jpg") == 0 || strcmp(extension,"jpeg") == 0){
        type = "image/jpeg";
    }else{
        type = "text/plain";
    }

    fpsock = fdopen(fd,"w");
    fpfile = fopen(f,"r");
    if( fpsock != NULL && fpfile != NULL){
        bytes = http_reply(fd,&fpsock,200,"OK",type,NULL);
        while( (c = getc(fpfile)) != EOF){
            putc(c,fpsock);
            bytes++;
        }
        fflush(fpsock);

        fclose(fpsock);
        fclose(fpfile);
    }
    server_bytes_sent += bytes;
}
