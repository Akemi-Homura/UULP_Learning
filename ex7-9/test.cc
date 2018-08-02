# include <stdio.h>
# include <unistd.h>
# include <signal.h>

void f(int){
    static int a = 5;
    printf("%d\n",a++);
}

int main(){
    signal(SIGINT,f);
    while(1){
        pause();
    }
    return 0;
}
