# include <stdio.h>
# include <unistd.h>
# include <signal.h>

# define SLPTIME 5

int main(){
    void f(int);
    signal(SIGINT,f);

    for(int i=0;i<5;i++){
        printf("Hello\n");
        sleep(SLPTIME);
    }
    return 0;
}

void f(int ){
    static int tot = 0;
    ++tot;
    printf("OUCH");
    for(int i=0;i<tot;i++){
        putchar('!');
    }
    putchar('\n');
}
