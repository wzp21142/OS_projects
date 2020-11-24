
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

static void sig_usr(int signo){
    if (signo == SIGINT)
        printf("received SIGINT,pid:%d\n",getpid());
    return;
}

int main(int argc, char ** argv)
{
    int sig;
    sig = fork();
    if(sig < 0){
        perror("Failed to create subprocess");
        return EXIT_FAILURE;
    }
    else if(sig == 0){
        printf("The child ID is %d\n", getpid());
        while(1){
            signal(SIGINT, sig_usr);
            pause();
        }
    }
    else{
        printf("The parent ID is %d\n", getpid());
        while(1){
            signal(SIGINT, sig_usr);
            pause();
        }
    }
    return EXIT_SUCCESS;
}

