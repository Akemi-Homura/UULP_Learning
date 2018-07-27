#ifndef STAT_UTIL_H
#define STAT_UTIL_H

# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>

struct stat get_file_status(int fd);

off_t get_file_size(int fd);

off_t get_file_size(const struct stat);

#endif
