# include <unistd.h>
# include <stdio.h>
# include <string.h>

int main(){
    char *arglist[3];

    arglist[0] = strdup("ls");
    arglist[1] = strdup("-l");
    arglist[2] = 0;

    printf("*** About to exec ls -l\n");
    execvp("ls",arglist);
    printf("*** is done. bty\n");
    return 0;
}
