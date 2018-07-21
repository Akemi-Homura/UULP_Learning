# include "spwd_util.h"
# include "inode_util.h"
# include "error_process.h"
# include <unistd.h>
# include <dirent.h>
# include <string.h>

#define BUFSIZE 1024

void ino_to_string(ino_t ino,char*);

void printpathto(ino_t ino){
    ino_t pino = get_ino("..");
    if(pino != ino){
        if(chdir("..") == -1){
            oops("Change directory failed!\n");
        }
        char name[BUFSIZE];
        ino_to_string(ino,name);
        printpathto(pino);
        printf("/%s",name);
    }
}

void ino_to_string(ino_t ino,char* name){
    DIR* dir_ptr;
    if((dir_ptr = opendir(".")) == NULL){
        oops("Open directory failed!\n");
    }
    struct dirent* dirtp;
    struct stat s_buf;
    while((dirtp = readdir(dir_ptr)) != NULL){
        if(!(strcmp(dirtp->d_name,".")&strcmp(dirtp->d_name,".."))){
            continue;
        }
        if(stat(dirtp->d_name,&s_buf) == -1){
            oops("Get file status failed! ",dirtp->d_name);
        }
        if(s_buf.st_ino == ino){
            strcpy(name,dirtp->d_name);
            closedir(dir_ptr);
            return;
        }
    }
    closedir(dir_ptr);
    fprintf(stderr,"Can't find same inode number %lld\n",ino);
    exit(1);
}
