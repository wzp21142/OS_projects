#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
int main() {
printf("Original\n");
pid_t result;
result = fork();
if (result < 0) {
perror("Failed to create process after <A>");
exit(1);
}
if(result==0){
	printf("Child 1\n");
	return (EXIT_SUCCESS);
}
else{
	printf("Parent\n");
	result = fork();
	if(result==0)
		printf("Child 2\n");
}
return (EXIT_SUCCESS);
}
