# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <ctype.h>

# define PRONAME "twordcount4"

struct arg_set{
    char *fname;
    int count;
    int index;
    pthread_mutex_t *lock;
    pthread_cond_t  *flag;
    struct arg_set  **mailbox;
};

void *count_words(void*);

int main(int ac,char** av){
    struct arg_set *mailbox = NULL;
    pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t  flag = PTHREAD_COND_INITIALIZER;

    pthread_t *thds;
    struct arg_set* args;
    int reports_in = 0;
    int total_words = 0;

    if ( ac < 2 ){
        fprintf(stderr,"usage: %s file ...\n",PRONAME);
        exit(1);
    }
    int filenum = ac - 1;
    args = (struct arg_set*)malloc(filenum * sizeof(struct arg_set));
    thds = (pthread_t*)malloc(filenum * sizeof(pthread_t));

    pthread_mutex_lock(&lock);

    for(int i = 0;i < filenum ;i++){
        args[i].fname       = av[i+1];
        args[i].count       = 0;
        args[i].index       = i;
        args[i].lock        = &lock;
        args[i].flag        = &flag;
        args[i].mailbox     = &mailbox;
    }

    for(int i=0;i < filenum;i++){
        pthread_create(&thds[i], NULL, count_words, &args[i]);
    }

    while(reports_in < filenum){
        printf("MAIN: waiting for flag to go up\n");
        pthread_cond_wait(&flag, &lock);
        printf("MAIN: Wow! flag was raised, I have the lock\n");
        printf("%5d: %s\n",mailbox->count, mailbox->fname);
        total_words += mailbox->count;

        pthread_join(thds[mailbox->index],NULL);

        mailbox = NULL;
        pthread_cond_signal(&flag);
        reports_in++;
    }
    printf("%5d: total words\n",total_words);
}

void *count_words(void* a){
    struct arg_set* args = (struct arg_set*)a;
    FILE* fp;
    int c,prevc = '\0';

    if ( (fp = fopen(args->fname,"r")) != NULL ){
        while( ( c = getc(fp)) != EOF ){
            if(!isalnum(c) && isalnum(prevc)){
                args->count++;
            }
            prevc = c;
        }
        fclose(fp);
    }else{
        perror(args->fname);
    }

    printf("COUNT: waiting to get lock\n");
    pthread_mutex_lock(args->lock);
    printf("COUNT: have lock, storing data\n");
    if ( *args->mailbox != NULL ){
        pthread_cond_wait(args->flag,args->lock);
    }
    *args->mailbox = args;
    printf("COUNT: raising flag\n");
    pthread_cond_signal(args->flag);
    printf("COUNT: unlocking box\n");
    pthread_mutex_unlock(args->lock);
    return NULL;
}
