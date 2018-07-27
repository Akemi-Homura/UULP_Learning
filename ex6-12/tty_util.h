#ifndef TTY_UTIL_H
#define TTY_UTIL_H

# define TTY_MODE_SAVE 0
# define TTY_MODE_RESET 1

void tty_mode(int how);
void set_no_echo();
void set_no_delay();

#endif
