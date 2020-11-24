#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>

int main(void){
    while(1) {
        int length, redirect_flag = 0;
        //redirect_flag 0:no-redirect,1:input-redirect,2:output-redirect,3:input and output redirect
        char command[255];
        fgets(command, 255, stdin);//read data per line from std.
        if(strcmp(command, "quit\n") == 0)
            exit(0);
        int arg_num = 0, t = 1;
        int pid = fork();
        if (pid < 0) {
            perror("Failed to create child");
            exit(1);
        }
        else if (pid == 0) {//child
            length = (int) strlen(command) - 1;
            command[length] = '\0';//cover '\n'
            for (int i = 0; i < length; i++) {//search for redirect signal.
                if (command[i] == '<') {
                    redirect_flag = 1;
                    break;
                } else if (command[i] == '>') {
                    redirect_flag = 2;
                    break;
                }
            }
            for (int j = 0; j < length; j++) {
                if (command[j] == ' ' || command[j] == '\t') {
                    arg_num++;
                    command[j] = '\0';
                }
            }
            if (!redirect_flag) {
                char **coms = (char **) malloc((arg_num + 2) * sizeof(char *));
                char *temp = "";
                coms[0] = temp;
                for (int j = 0; j < length; j++) {
                    if (command[j] == '\0') {
                        coms[t++] = &command[j + 1];
                    }
                }
                coms[arg_num + 1] = NULL;
                if (execvp(command, coms) == -1) {
                    perror("In child process, failed to exec a program");
                    exit(1);
                }
            }
            else {
                FILE *pipeW,*pipeR, *file_pointer;
                char buffer[255], *file;
                int count = 0;
                for (int s = (int) strlen(command);; s++) {
                    if (command[s] != '\0') {
                        count++;
                        if (count == 2) {
                            file = &command[s];
                            break;
                        }
                    }
                }
                if (redirect_flag == 1) {//input-redirect
                    pipeR = popen(command, "w");
                    file_pointer = fopen(file, "r");
                    if (pipeR == NULL || file_pointer == NULL) {
                        perror("In child process, error in opening the pipe/file");
                        exit(1);
                    }
                    while (fgets(buffer, 255, file_pointer))
                        fprintf(pipeR, "%s", buffer);
                   pclose(pipeR);
                }
                else {//output-redirect
                    pipeW = popen(command, "r");
                    file_pointer = fopen(file, "w");
                    while (fgets(buffer, 255, pipeW))
                       fprintf(file_pointer, "%s", buffer);
                    if (pipeW == NULL || file_pointer == NULL) {
                        perror("In child process, error in opening the pipe/file");
                        exit(1);
                    }
                    pclose(pipeW);
                }
                fclose(file_pointer);
            }
            printf("Redirection done.\n");
            return EXIT_SUCCESS;
        }
        else
            wait(NULL);
    }
    return EXIT_SUCCESS;
}