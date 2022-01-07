#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>

int main(int argc,char *argv[]){
	int a,b;
	pid_t pid;
	char n1[50],n2[50];
	scanf("%d%d",&a,&b);
	sprintf(n1,"%d",a);
	sprintf(n2,"%d",b);
	
	for(int i=1;i<=4;i++){
		pid = fork();
		if(pid < 0){
			printf("Child is not created\n");
			exit(0);
		}
		else if(pid == 0){
			if(i==1){
				execlp("./sum","summation",n1,n2,NULL);
			}
			else if(i==2){
				execlp("./sub","subtrction",n1,n2,NULL);
			}
			else if(i==3){
				execlp("./mul","multiplication",n1,n2,NULL);
			}
			else{
				execlp("./div","division",n1,n2,NULL);
			}
		}
		else if(pid > 0){
			wait(NULL);
		}
	}
	return 0;
}

