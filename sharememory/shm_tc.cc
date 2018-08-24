# include <stdio.h>
# include <sys/shm.h>
# include <time.h>
# include <stdlib.h>
# include <string.h>

# define TIME_MEM_KEY 99
# define SEG_SIZE ((size_t)100)
# define oops(m,x) {perror(m); exit(x);}

int main(){
    int     seg_id;
    char    *mem_ptr;

    /* create a shared memory segment */
    seg_id = shmget(TIME_MEM_KEY, SEG_SIZE, 0777);
    if( seg_id == -1 ){
        oops("shmget" ,1);
    }

    /* attach to it and get a pointer to where it attaches */
    mem_ptr = (char*)shmat( seg_id, NULL, 0);
    if( mem_ptr == (void*)-1 ){
        oops("shmat",2);
    }
    printf("The time, direct from memory: .. %s\n",mem_ptr);
    shmdt( mem_ptr );
}
