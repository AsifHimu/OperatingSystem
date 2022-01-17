#define _GNU_SOURCE
#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<sched.h>

int main(int argc,char *argv[]){
	pid_t status,pid1,pid2,pid,val1,val2,val3,cpu;
	char n1[50],n2[50],n3[50],n4[50];
		pid1 = fork();
		if(pid1 == 0){
			while(1){
				val1 = getpid();
				cpu = sched_getcpu();
				sprintf(n1,"%d",val1);
				sprintf(n2,"%d",cpu);
				execlp("./Pillow","Pillow",n1,n2,NULL);
			}
		}
		else{
			pid2 = fork();
			if(pid2 == 0){
				while(1){
					val2 = getpid();
					cpu = sched_getcpu();
					sprintf(n3,"%d",val2);
					sprintf(n4,"%d",cpu);
					execlp("./Killow","Killow",n3,n4,NULL);
				}
			}
			else{
				while(1){
					wait(NULL);
					val3 = getpid();
					printf("Process-%u,Parent of Pillow %u and Killow %u,running at CPU-%d\n",val3,pid1,pid2,sched_getcpu());
				}
			}
		}
	return 0;
}
