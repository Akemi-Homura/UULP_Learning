# ifndef VARLIB_H
# define VARLIB_H

int VLstore(const char *var,const char *val);

char* VLlookup(const char *name);

void VLlist();

int VLenviron2table(char**);

char** VLtable2environ();

int VLexport(const char* name);

# endif
