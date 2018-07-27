# ifndef MORE_UTIL_H
# define MORE_UTIL_H
# include <stdio.h>

# define S_MULTI 01
# define S_DFL 0

# define S_IS_MULTI(mode) ((mode&S_MULTI))

void do_more(int,const char*,const char* = NULL);
void ctrl_c_handler(int);
void ctrl_quit_handler(int);


# endif
