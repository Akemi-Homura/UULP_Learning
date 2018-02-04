# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <pwd.h>
# include <uuid/uuid.h>

int main(){
    int euid = geteuid();
    passwd* record = getpwuid(euid);
    printf("%s\n",record->pw_name);
    return 0;
}
