# include <stdio.h>
# include <string.h>
# include <ctype.h>
# include "smsh.h"
# include "varlib.h"

int assign(char *);
int okname(char *);

int builtin_command(char **args,int *resultp){
    int rv = 0;
    if( strcmp(args[0],"set") == 0 ){
        VList();
        *resultp = 0;
        rv = 1;
    }else if( strchr(args[0], '=') != NULL ){
        *resultp = assign(args[0]);
    }
}
