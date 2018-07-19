#ifndef COPY_UTIL_H
#define COPY_UTIL_H

void copy_dir(const char* src,const char* dst);
void copy_file(const char* src,const char* dst);
char* merge_path(const char*,const char*);

#endif
