# include "more_util.h"
# include "screensz.h"
# include <stdlib.h>
# include "tty_util.h"
# include "stat_util.h"
# include <string.h>

# define COLSIZE 512
# define NO_FILE_SIZE -1
# define MAX_PERCENT 100
# define oops(s,x) {perror(s); exit(x);}
# define TTY "/dev/tty"
# define QUIT 0
# define NTL  1
# define NTP  2
# define BEEP putchar('\a')
# define FILE_HEADER "::::::::::::::\n%s\n::::::::::::::\n"

# define RELEASE 0
# define DEBUG 1
# define RUNTYPE RELEASE

void do_more(int,int,const char* name,const char* nxname);

int see_more(FILE* tty,int,const char* = NULL);

void EXIT(int x,FILE*);

void do_more(int mode,const char* cur_name,const char* nxt_name){
    do_more(mode,get_row_num(),cur_name,nxt_name);
}

void do_more(int mode,int row_num,const char* cur_name,const char* nxt_name){
    tty_mode(TTY_MODE_SAVE);
    set_no_echo();
    row_num--;
    char buf[COLSIZE];
    int num_of_lines = 0,reply;
    FILE* fp_tty,*fp;
    if((fp_tty = fopen(TTY,"r")) == NULL){
        oops("fopen",1);
    }
    if( (fp = fopen(cur_name,"r")) == NULL){
        oops("fopen",1);
    }
    int fd = fileno(fp);
    if(fd == -1){
        oops("fileno",1);
    }
    if(S_IS_MULTI(mode)){
        printf(FILE_HEADER,cur_name);
        num_of_lines = 3;
    }
    off_t file_size = get_file_size(fd);
    off_t cur_size = 0;
    int percent = -1;
    while(fgets(buf,COLSIZE,fp) != NULL){
        int len = strlen(buf);
        cur_size += len;
        if(num_of_lines == row_num || cur_size == file_size){
            if(cur_size == file_size){
                printf("%s",buf);
            }
            if(file_size != NO_FILE_SIZE){
                percent = cur_size * 100 / file_size;
            }
#if RUNTYPE == DEBUG
            printf("cur_size:%ld tot_size:%ld percent:%d\n",cur_size,file_size,percent);
#endif
            reply = see_more(fp_tty,percent,nxt_name);
            printf("\33[A\n\33[K");
            switch(reply){
                case QUIT:
                    EXIT(0,fp);
                case NTL:
                    --num_of_lines;
                    break;
                case NTP:
                    num_of_lines -= row_num;
                    break;
                default:
                    fprintf(stderr,"Unexcepted reply %d\n",reply);
                    EXIT(1,fp);
            }
        }
        printf("%s",buf);
        num_of_lines++;
    }
}

int see_more(FILE* tty,int percent,const char* nxt_name){
    if(percent == MAX_PERCENT ){
        if(nxt_name != NULL){
            printf("\033[7m--More--(Next file: %s)\033[m",nxt_name);
        }else{
            return QUIT;
        }
    }else if(percent != NO_FILE_SIZE){
        printf("\033[7m--More--(%d%%)\033[m",percent);
    }else{
        printf("\033[7m--More--\033[m");
    }
    char c;
    while((c = getc(tty)) != EOF){
        switch(c){
            case 'q':
            case 'Q':
                return QUIT;
            case ' ':
                return NTP;
            case '\n':
                return NTL;
        }
        BEEP;
    }
    EXIT(0,tty);
    return QUIT;
}

inline void EXIT(int v,FILE* fp){
    tty_mode(TTY_MODE_RESET);
    fclose(fp);
    exit(v);
}
