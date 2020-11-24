#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <semaphore.h>
#define n 5
//缓冲池及其头尾指针
int pool[n],in=0,out=0;
//互斥锁
pthread_mutex_t mutex;
//缓冲池空满信号量
sem_t empty,full;

void* producer(void* arg){
    const char* filename=(const char*)arg;
    FILE* file=fopen(filename,"r");
    if(file!=NULL){
        for(int i=0;i<10;){
            sem_wait(&empty);
            pthread_mutex_lock(&mutex);
            fscanf(file,"%d",&pool[in]);
            printf("put %d into pool[%d]\n",pool[in],in);
            in=(in+1)%n;
            i++;
            pthread_mutex_unlock(&mutex);
            sem_post(&full);
        }
    }
    fclose(file);
    pthread_exit(NULL);
}

 void* calculator(void* arg){
    const int* flag=(const int*)arg;//0:+ 1:*
    for(int i=0;i<10;){
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        int temp1,temp2;
        if(i%2){
            temp1=pool[out];
            out=(out+1)%n;
        }
        else{
            temp2=pool[out];
            out=(out+1)%n;
        }
        if(i%2){
            if(*flag)
                printf("%d * %d = %d\n",temp1,temp2,temp1*temp2);
            else
                printf("%d + %d = %d\n",temp1,temp2,temp1+temp2);
        }
        i++;
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
    }
    pthread_exit(NULL);
}

int main(){
    pthread_t tid_p1,tid_p2;
    pthread_t tid_c1,tid_c2;
    //初始化互斥锁
    pthread_mutex_init(&mutex,NULL);
    //初始化信号量
    sem_init(&empty,0,n);
    sem_init(&full,0,0);
    //生产者线程
    int a=0,b=1;
    int*c1=&a,*c2=&b;
    char* t1= (char *)malloc(10);
    strcpy(t1,"data1.txt");
    char* t2= (char *)malloc(10);
    strcpy(t2,"data2.txt");
    pthread_create(&tid_p1,NULL,producer,(void *)t1);
    pthread_create(&tid_p2,NULL,producer,(void *)t2);
    pthread_create(&tid_c1,NULL,calculator,(void *)c1);
    pthread_create(&tid_c2,NULL,calculator,(void *)c2);
    //等待
    pthread_join(tid_p1,NULL);
    pthread_join(tid_p2,NULL);
    pthread_join(tid_c1,NULL);
    pthread_join(tid_c2,NULL);

    pthread_mutex_destroy(&mutex);
    return 0;
}
