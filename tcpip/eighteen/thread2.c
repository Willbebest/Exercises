#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

void* thread_main(void* arg);

int main(int argc, char** argv)
{
    pthread_t thid;
    int thread_param=5;
    void *th_ret;

    if(pthread_create(&thid, NULL, thread_main, (void*)&thread_param)!=0)
    {
        puts("pthread_create() error");
        return -1;
    }

    if(pthread_join(thid, &th_ret)!=0)
    {
        puts("pthread_join() error");
        return -1;
    }

    printf("Thread return message: %s \n", (char*)th_ret);

    free(th_ret);
    return 0;
}

void* thread_main(void *arg)
{
    int cnt=*((int*)arg);
    char *msg=(char*)malloc(sizeof(char)*50);
    strcpy(msg, "hello, I'm thread~\n");

    for(int i=0; i<cnt; i++)
    {
        sleep(1);
        puts("running thread");
    }

    return (void*)msg;
}
