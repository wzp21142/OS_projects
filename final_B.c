#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>

struct msgbuf {
    long mtype;
    char mtext[50];
}msgbuf;

int main(int argc, char **argv)
{
    struct msgbuf message;
    int qid = msgget((key_t)185, IPC_CREAT | 0666);
    if (qid == -1)
    {
        perror("Failed in calling msgget!\n");
        return EXIT_FAILURE;
    }
    int type=111;
    for(int i = 0; i < 10; i++)
    {
        if (msgrcv(qid, (void *)&message, 50, --type, 0) == -1)
            perror("Failed in calling msgrcv!\n");
        printf("%ld,%s\n", message.mtype,message.mtext);
    }
    if (msgctl(qid, IPC_RMID, 0) == -1)
        perror("Failed in calling msgctl!\n");
    return EXIT_SUCCESS;
}