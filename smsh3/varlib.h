# ifndef VARLIB_H
# define VARLIB_H

# define MAXVARS 1024

struct var{
    char *str;
    int global;
};

static struct var tab[MAXVARS];

void VLstore(char *var,char *val);

char* VLookup(char *var);

void VList();

# endif
