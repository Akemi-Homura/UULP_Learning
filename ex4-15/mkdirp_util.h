#ifndef MKDIRP_UTIL_H
#define MKDIRP_UTIL_H

# include <sys/stat.h>

void create_dir(const char* path,mode_t mode,bool has_intermediate);

void create_dir(const char* path,bool has_intermediate);

#endif
