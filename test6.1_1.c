#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/ipc.h>
struct msgbuf {
    long mtype;
    char mtext[1024];
}msgbuf;

int main(void){
    struct msgbuf writebuf;
    int qid = msgget((key_t)1807, IPC_CREAT | 0777);
    if(qid == -1){
        perror("Failed in calling msgget!\n");
        return (-1);
    }
    for(int i=0;i<10;i++){
        fgets(writebuf.mtext, 1024,stdin);
        writebuf.mtype = 10;
        if (msgsnd(qid, (void *)&writebuf, 1024, 0) == -1)
        {
            fprintf(stderr, "Failed in calling msgsnd!\n");
            exit(EXIT_FAILURE);
        }
    }
    return EXIT_SUCCESS;
}