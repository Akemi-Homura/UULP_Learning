# include "umask.h"

mode_t getumask(){
    mode_t mask = umask(0);
    umask(mask);
    return mask;
}
