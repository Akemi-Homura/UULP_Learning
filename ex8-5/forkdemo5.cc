# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>

# define TESTFILE "test.txt"

int main(){
    FILE* fp;
    int pid;
    const char *msg1 = "Test 1 2 3 ..\n";
    const char* msg2 = "Hello ,hello\n";

    if( (fp = fopen(TESTFILE,"w")) == NULL){
        return 0;
    }
    fprintf(fp,"%s",msg1);
    // fflush(fp);

    if((pid = fork()) == -1){
        return 0;
    }
    fprintf(fp,"%s",msg2);
    fclose(fp);
    return 1;
}
