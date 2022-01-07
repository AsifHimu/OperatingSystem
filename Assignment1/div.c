#include<stdio.h>
#include<stdlib.h>

int main(int argc,char *argv[]){
	int a=atoi(argv[1]);
	int b=atoi(argv[2]);
	printf("The division is %.2f\n",(float)a/(float)b);	
	return 0;
}
