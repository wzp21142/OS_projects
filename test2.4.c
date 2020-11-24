#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define INPUT 0
#define OUTPUT 1

int main(void){
    int pipe1[2], pipe2[2];
    char buf[256];
    char *message1 = "Child 1 is sending a message!";
    char *message2 = "Child 2 is sending a message!";
    int bytes_read;
    int result;
    if(pipe(pipe1)){
        perror("Failed in calling pipe");
        exit(1);
    }
    result = fork();
    if(result < 0){
        perror("Failed in calling fork");
        exit(1);
    }
    else if(result != 0){
        if(pipe(pipe2)){
            perror("Failed in calling pipe");
            exit(1);
        }
        result = fork();
        if(result < 0){
            perror("Failed in calling fork");
            exit(1);
        }
        else if(result == 0){//child 2
            if(write(pipe2[OUTPUT], message2, strlen(message2)) <0){
                perror("In child 2, failed to sending message");
                exit(1);
            }
        }
        else{//parent
            bytes_read = read(pipe1[INPUT], buf, sizeof(buf));
            if(bytes_read < 0){
                perror("In Parent, failed to receive message from child1");
                exit(1);
            }
            else{
                buf[bytes_read] = '\0';
                printf("%d bytes of data received from child1: %s\n", bytes_read, buf);
            }
            bytes_read = read(pipe2[INPUT], buf, sizeof(buf));
            if(bytes_read < 0){
                perror("In Parent, failed to receive message from child2");
                exit(1);
            }
            else{
                buf[bytes_read] = '\0';
                printf("%d bytes of data received from child2: %s\n", bytes_read, buf);
            }
        }
    }
    else{//child 1
        if(write(pipe1[OUTPUT], message1, strlen(message1)) <0){
            perror("In child 1, failed to sending message");
            exit(1);
        }
    }
    return 0;
}

