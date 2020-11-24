#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define NUM_THREADS 2
void *Thread_Int(void *paraInt) {
    int *num = (int *)paraInt;
    printf("Int:%d,thread_self:%ld\n", *num, (long)pthread_self());
    pthread_exit(NULL);
}

void *Thread_Char(void *paraCh) {
    char *ch = (char *)paraCh;
    printf("Char:%c,thread_self:%ld\n", *ch, (long)pthread_self());
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    pthread_t thread[NUM_THREADS];
    pthread_attr_t attr;
    int rc1,rc2;
    int num=1024,*paraInt=&num;
    char ch='P',*paraCh=&ch;
    void *status;
    /* Initialize and set thread detached attribute */
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    printf("Main: creating thread\n");
    rc1 = pthread_create(&thread[0], &attr, Thread_Int, (void *) paraInt);
    rc2 = pthread_create(&thread[1], &attr, Thread_Char, (void *) paraCh);
    if (rc1) {
        printf("ERROR; return code from pthread_create() is %d\n", rc1);
        exit(-1);
    }
    if (rc2) {
        printf("ERROR; return code from pthread_create() is %d\n", rc2);
        exit(-1);
    }
    /* Free attribute and wait for the other threads */
    pthread_attr_destroy(&attr);
    rc1 = pthread_join(thread[0], &status);
    rc2 = pthread_join(thread[1], &status);
    if (rc1) {
        printf("ERROR; return code from pthread_join() is %d\n", rc1);
        exit(-1);
    }
    if (rc2) {
        printf("ERROR; return code from pthread_join() is %d\n", rc2);
        exit(-1);
    }
    printf("Main: completed join with thread %d having a status of %ld\n",0, (long) status);
    printf("Main: completed join with thread %d having a status of %ld\n",1, (long) status);
    printf("Main: program completed. Exiting.\n");
    pthread_exit(NULL);
}