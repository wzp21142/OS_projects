#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
struct membuf {
    long written;
    char mtext[1024];
}membuf;

int main(void){
    int qid = shmget((key_t)1807, sizeof(struct membuf), IPC_CREAT | 0777);
    if(qid == -1){
        perror("Failed in calling shmget!\n");
        return (-1);
    }
    void* memptr_temp = shmat(qid, 0, 0);
    if (memptr_temp == (void *)-1)
    {
        perror("Failed in calling shmat!\n");
        return EXIT_FAILURE;
    }
    struct membuf* memptr = (struct membuf*)memptr_temp;
    fgets(memptr->mtext, 1024,stdin);
    memptr->written =1 ;
    if (shmdt(memptr) == -1)
    {
        fprintf(stderr, "Failed in calling memptr!\n");
        exit(EXIT_FAILURE);
    }
    return EXIT_SUCCESS;
}