# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/stat.h>

# define STAT_F 01
# define STAT_DIR 02
# define STAT_R 04
# define STAT_W 8
# define S_IS_EXIST(mode) ((mode&STAT_F) == STAT_F)
# define S_IS_DIR(mode) ((mode&STAT_DIR) == STAT_DIR)
# define S_IS_R(mode) ((mode&STAT_R) == STAT_R)
# define S_IS_W(mode) ((mode&STAT_W) == STAT_W)

bool is_dir(const char* path);
bool is_exist(const char* path);
bool is_readable(const char* path);
bool is_writable(const char* path);

void check_stat(const char*path,int& res);
