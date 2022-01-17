#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main(int argc,char *argv[]){
	printf("I am child-%s running at CPU-%s\n",argv[1],argv[2]);
	return 0;
}
