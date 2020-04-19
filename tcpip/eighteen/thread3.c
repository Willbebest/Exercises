#include <stdio.h>
#include <pthread.h>

void* thread_summation(void* arg);
int sum=0;

int main(int argc, char** argv)
{
    pthread_t thid1, thid2;
    int range1[]={1, 5};
    int range2[]={6, 10};

    pthread_create(&thid1, NULL, thread_summation, (void*)range1);
    pthread_create(&thid2, NULL, thread_summation, (void*)range2);

    printf("thid1=%ld\n", thid1);
    printf("thid2=%ld\n", thid2);

    pthread_join(thid1, NULL);
    pthread_join(thid2, NULL);
    printf("result: %d \n", sum);

    return 0;
}

void* thread_summation(void* arg)
{
    int start=((int*)arg)[0];
    int end=((int*)arg)[1];

    while(start<=end)
    {
        sum+=start;
        printf("%ld: sum=%d\n", pthread_self(), sum);
        start++;
    }
    return NULL;
}
