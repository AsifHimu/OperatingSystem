#define _GNU_SOURCE
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<sched.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
	pid_t cpid1,cpid2,pid;
	int cpuN,policy,cpuID;
	cpu_set_t mask;
	
	cpid1 = fork();
	
	if(cpid1 == 0){ //nebula
		for(int i=1;i<=100;i++){
			execlp("./Nebula","NEBULA",NULL);
		}
	}
	else{
		cpid2 = fork();
		if(cpid2 == 0){ //blackhole
			for(int i=1;i<=100;i++){
				execlp("./BlackHole","BLACKHOLE",NULL);
			}
		}
		else{
			wait(NULL);
			cpuID = sched_getcpu();
			pid = getpid();
			cpuN = sysconf(_SC_NPROCESSORS_ONLN);
			policy = sched_getscheduler(0);
			printf("MainProcess Running CpuID, Policy ,PID and No. of CPUs: %d %d %d %d\n",cpuID,policy,pid,cpuN);
			sched_getaffinity(0,sizeof(cpu_set_t),&mask);
			printf("MainProcess CPU affinity :");	
			for(int i=0;i<cpuN;i++){
				printf("%d ",CPU_ISSET(i,&mask));
			}
			printf("\n");		
			//printf("ALL scheduling policies are: %d %d %d %d %d\n",SCHED_OTHER,SCHED_FIFO,SCHED_BATCH,SCHED_RR,SCHED_IDLE);
			cpuID = sched_getcpu();
			printf("MainProcess Changed CPU ID : %d\n",cpuID);
		}
	}
	return 0;
}
