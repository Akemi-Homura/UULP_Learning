# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <ctype.h>

int total_words;
pthread_mutex_t counter_lock = PTHREAD_MUTEX_INITIALIZER;

# define PRONAME "twordcount2"
# define RELEASE    0
# define DEBUG      1
# define RUNTYPE    RELEASE

void * count_words(void *);

int main(int ac,char **av){
    pthread_t *thds;

    if( ac < 2 ){
        printf("usage: %s file ...\n",PRONAME);
        exit(1);
    }

    int filenum = ac - 1;
    thds = (pthread_t*)malloc(filenum * sizeof(pthread_t));

    total_words = 0;
    for(int i=0;i<filenum;i++){
        pthread_create(&thds[i], NULL, count_words, (void*)av[i+1]);
    }
    for(int i=0;i<filenum;i++){
        pthread_join(thds[i], NULL);
    }
    printf("%5d: total_words\n",total_words);
    free(thds);
    return 0;
}

void *count_words(void *f){
    const char* filename = (const char*)f;
#if RUNTYPE == DEBUG
    printf("filename: %s\n",filename);
#endif
    FILE* fp;
    int c,prevc = '\0';
    if((fp = fopen(filename,"r")) != NULL){
        while( (c = getc(fp)) != EOF){
            if( !isalnum(c) && isalnum(prevc)){
                pthread_mutex_lock(&counter_lock);
                total_words++;
                pthread_mutex_unlock(&counter_lock);
            }
            prevc = c;
        }
        fclose(fp);
    }else{
        perror(filename);
    }
    return NULL;
}
