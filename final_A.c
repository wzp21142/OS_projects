#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/ipc.h>
struct msgbuf {
    long mtype;
    char mtext[50];
}msgbuf;

int main(void){
    struct msgbuf writebuf;
    int qid = msgget((key_t)185, IPC_CREAT | 0666);
    if(qid == -1){
        perror("Failed in calling msgget!\n");
        return (-1);
    }
    writebuf.mtype=100;
    for(int i=0;i<10;i++){
        fgets(writebuf.mtext, 50,stdin);
        writebuf.mtype++;
        if (msgsnd(qid, (void *)&writebuf, 50, 0) == -1)
        {
            fprintf(stderr, "Failed in calling msgsnd!\n");
            exit(EXIT_FAILURE);
        }
    }
    return EXIT_SUCCESS;
}