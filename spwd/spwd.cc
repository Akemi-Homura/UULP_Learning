# include <stdio.h>
# include "spwd_util.h"
# include "inode_util.h"

int main(){
   printpathto(get_ino("."));
   putchar('\n');
   return 0;
}
