# ifndef SMSH_H
# define SMSH_H

# include <sys/types.h>
# include <stdio.h>

# define YES 1
# define NO  0

char *next_cmd(char*,FILE*);
char **splitline(char*);
void freelist(char **);
void *emalloc(size_t);
void *erealloc(void*,size_t);
int  execute(char**);
void fatal(const char* ,const char *,int);

#endif
