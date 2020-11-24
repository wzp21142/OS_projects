
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char **argv){
	char buffer[1024];
	if(argc!=3){
		printf("参数输入错误!\n");
		exit(1);
	}
	FILE *in,*out;
	if((in=fopen(argv[1],"r"))==NULL){
		printf("源文件不存在！\n");
		exit(1);
	}
	if((out=fopen(argv[2],"w"))==NULL){
		printf("创建目标文件失败！\n");
		exit(1);
	}
	int len;
	while((len=fread(buffer,1,1024,in))>0){
		fwrite(buffer,1,len,out);
	}
    printf("Success！\n");
	fclose(out);
	fclose(in);
	return 0;
}