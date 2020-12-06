#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int i=0, result;
    pid_t pid;
    char* split = " ";
    char *temp[256];
    char str[256];
    while(1){
        printf("please input a instruction:");
        fgets(str,256,stdin);
        printf("str=%s",str);
        str[strlen(str)-1] = '\0';
        if(strcmp(str, "quit\n") == 0)
            break;
        temp[0]= strtok(str, split);
        while (temp[i]!= NULL) {
            printf("%s\n", temp[i]);
            i++;
            temp[i] = strtok(NULL, split);
        }
        printf("1");
        /*if (argc <= 1) {
            printf("Input error\n");
            exit(1);
        }
        for (i = 1; i < argc; i++) {
            temp[i - 1] = argv[i];
        }
        temp[argc - 1] = NULL;*/
        pid = fork();
        if (pid < 0) {
            perror("Failed to create child");
            exit(1);
        }
        else if (pid == 0) {
            // Child
            printf("succcess to create child");
            result = execvp(temp[0], temp);
            printf("result=%d",result);
            if (result == -1) {
                perror("In child process, failed to exec a program");
            }
            exit(1);
        }
        else {
            // Parent
            wait(&result);
            printf("\n\033[1;32m Value returned from child process, result = %d\033[0m\n", result);
            printf("\033[1;32m WEXITSTATUS(result) = %d\033[0m\n", WEXITSTATUS(result));
        }
    }
    return 0;
}