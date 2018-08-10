# include <stdio.h>
# include <string.h>
# include <ctype.h>
# include "smsh.h"
# include "varlib.h"

# define SET "set"
# define EXPORT "export"

int assign(const char *);
int okname(const char *);

int builtin_command(char **args,int *resultp){
    int rv = 0;
    if( strcmp(args[0],SET) == 0 ){
        VLlist();
        *resultp = 0;
        rv = 1;
    }else if( strchr(args[0], '=') != NULL ){
        *resultp = assign(args[0]);
        if( *resultp != -1){
            rv = 1;
        }
    }else if( strcmp(args[0],EXPORT) == 0){
        if( args[1] != NULL && okname(args[1]) ){
            *resultp = VLexport(args[1]);
        }else{
            *resultp = 1;
        }
        rv = 1;
    }
    return rv;
}

int assign(const char* str){
    char *cp;
    int rv;

    /*
     * split and merge string
     */
    cp = strchr(str,'=');
    *cp = '\0';
    rv = (okname(str)?VLstore(str,cp+1):-1);
    *cp = '=';
    return rv;
}

int okname(const char* str)
/*
 * returns: 0 for no,1 for yes
 */
{
    const char *cp;

    for(cp = str; *cp; cp++){
        if((isdigit(*cp) && cp == str) || !(isalnum(*cp) || *cp=='_')){
            return 0;
        }
    }
    return (cp != str);
}
