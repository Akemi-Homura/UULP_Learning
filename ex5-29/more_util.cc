# include "more_util.h"
# include "screensz.h"
# include <stdlib.h>

# define COLSIZE 512
# define oops(s,x) {perror(s); exit(x);}
# define TTY "/dev/tty"
# define QUIT 0
# define NTL  1
# define NTP  2

void do_more(FILE* fp,int);

int see_more(FILE* tty);

void do_more(FILE* fp){
    do_more(fp,get_row_num());
}

void do_more(FILE* fp,int row_num){
    -- row_num;
    char buf[COLSIZE];
    int num_of_lines = 0,reply;
    FILE* fp_tty;
    if((fp_tty = fopen(TTY,"r")) == NULL){
        oops("fopen",1);
    }
    while(fgets(buf,COLSIZE,fp) != NULL){
        if(num_of_lines == row_num){
            reply = see_more(fp_tty);
            switch(reply){
                case QUIT:
                    exit(0);
                case NTL:
                    --num_of_lines;
                    break;
                case NTP:
                    num_of_lines -= row_num;
                    break;
                default:
                    fprintf(stderr,"Unexcepted reply %d\n",reply);
                    exit(1);
            }
            printf("\33[A\33[K");
        }
        printf("%s",buf);
        num_of_lines++;
    }
}

int see_more(FILE* tty){
    printf("\033[7m more? \033[m");
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
    }
    exit(1);
}
