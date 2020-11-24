#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
struct membuf {
    long written;
    char mtext[1024];
}membuf;

int main(int argc, char **argv)
{
    int qid = shmget((key_t)1807, sizeof(struct membuf),IPC_CREAT | 0777);
    if (qid == -1)
    {
        perror("Failed in calling shmget!\n");
        return EXIT_FAILURE;
    }
    void* memptr_temp = shmat(qid, 0, 0);
    if (memptr_temp == (void *)-1)
    {
        perror("Failed in calling shmat!\n");
        return EXIT_FAILURE;
    }
    struct membuf* memptr = (struct membuf*)memptr_temp;
    if(memptr->written)
        printf("got:%s\n",memptr->mtext);
    memptr->written=0;
    if (shmdt(memptr) == -1)
    {
        perror("Failed in calling shmdt!\n");
        return EXIT_FAILURE;
    }
    
    if (shmctl(qid, IPC_RMID, 0) == -1)
    {
        perror( "Failed in calling shmctl!\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}