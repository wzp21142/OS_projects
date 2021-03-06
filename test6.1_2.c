#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>

struct msgbuf {
    long mtype;
    char mtext[1024];
}msgbuf;

int main(int argc, char **argv)
{
    struct msgbuf message;
    int qid = msgget((key_t)1807, IPC_CREAT | 0777);
    if (qid == -1)
    {
        perror("Failed in calling msgget!\n");
        return EXIT_FAILURE;
    }

    for(int i = 0; i < 10; i++)
    {
        if (msgrcv(qid, (void *)&message, 1024, 10, 0) == -1)
            perror("Failed in calling msgrcv!\n");
        printf("%s", message.mtext);
    }
    if (msgctl(qid, IPC_RMID, 0) == -1)
        perror("Failed in calling msgctl!\n");
    return EXIT_SUCCESS;
}