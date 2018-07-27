# ifndef SCREENSZ_H
# define SCREENSZ_H

# include <sys/ioctl.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>

struct winsize get_winsize();

# endif
