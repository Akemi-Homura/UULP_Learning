# include <unistd.h>
# include <stdio.h>

int main(){
    printf("%s\n",ttyname(STDIN_FILENO));
    return 0;
}
