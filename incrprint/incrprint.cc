# include <stdio.h>
# include <unistd.h>
# include <pthread.h>

# define NUM 5

void* pirnt_count(void *);

int counter = 0;

int main(){
    pthread_t t1;
    void *pirnt_count(void *);
    pthread_create(&t1, NULL, pirnt_count, NULL);
    for(int i = 0; i < NUM; i++){
        counter++;
        sleep(1);
    }
    pthread_join(t1, NULL);
}

void *pirnt_count(void *){
    for(int i=0;i < NUM;i++){
        printf("count = %d\n",counter);
        sleep(1);
    }
    return NULL;
}
