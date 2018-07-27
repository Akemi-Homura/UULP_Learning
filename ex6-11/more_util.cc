# include "more_util.h"
# include "screensz.h"
# include <stdlib.h>
# include "tty_util.h"
# include "stat_util.h"
# include <string.h>

# define COLSIZE 512
# define NO_FILE_SIZE -1
# define oops(s,x) {perror(s); exit(x);}
# define TTY "/dev/tty"
# define QUIT 0
# define NTL  1
# define NTP  2
# define BEEP putchar('\a')

# define RELEASE 0
# define DEBUG 1
# define RUNTYPE RELEASE

void do_more(FILE* fp,int);

int see_more(FILE* tty,int);

void EXIT(int x,FILE*);

void do_more(FILE* fp){
    do_more(fp,get_row_num());
}

void do_more(FILE* fp,int row_num){
    tty_mode(TTY_MODE_SAVE);
    set_no_echo();
    row_num--;
    char buf[COLSIZE];
    int num_of_lines = 0,reply;
    FILE* fp_tty;
    if((fp_tty = fopen(TTY,"r")) == NULL){
        oops("fopen",1);
    }
    int fd = fileno(fp);
    if(fd == -1){
        oops("fileno",1);
    }
    off_t file_size = get_file_size(fd);
    off_t cur_size = 0;
    int percent = -1;
    while(fgets(buf,COLSIZE,fp) != NULL){
        cur_size += strlen(buf);
        if(num_of_lines == row_num){
            if(file_size != NO_FILE_SIZE){
                percent = cur_size * 100 / file_size;
            }
#if RUNTYPE == DEBUG
            printf("cur_size:%ld tot_size:%ld percent:%d\n",cur_size,file_size,percent);
#endif
            reply = see_more(fp_tty,percent);
            switch(reply){
                case QUIT:
                    printf("\n");
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
            printf("\33[A\n\33[K");
        }
        printf("%s",buf);
        num_of_lines++;
    }
}

int see_more(FILE* tty,int percent){
    if(percent != NO_FILE_SIZE){
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
    printf("\033[A");
    fclose(fp);
    exit(v);
}
