#ifndef INODE_UTIL_H
#define INODE_UTIL_H

# include <sys/stat.h>
# include "error_process.h"

ino_t get_ino(const char*);

#endif
