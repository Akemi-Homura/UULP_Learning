# include <stdio.h>
# include <dirent.h>
# include <stdlib.h>

void do_ls(const char*);

int main(int argc,char * argv[]){
    if(argc == 1){
        do_ls(".");
    }else{
        while(--argc){
            do_ls(argv[argc]);
        }
    }
    return 0;
}

void do_ls(const char * path){
    DIR* dir_ptr;
    dirent* direntp;
    if((dir_ptr = opendir(path)) == NULL){
        fprintf(stderr,"ls01: cannot open %s\n",path);
    }else{
        while((direntp = readdir(dir_ptr)) != NULL){
            printf("%s\n",direntp->d_name);
        }
        closedir(dir_ptr);
    }
}
