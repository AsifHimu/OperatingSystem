#define _GNU_SOURCE
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<sched.h>
#include <sys/types.h>
#include <sys/wait.h>

void X(){
	int cpuN,policy,cpuID;
	cpu_set_t mask;
	pid_t pid;
	cpuID = sched_getcpu();
	pid = getpid();
	cpuN = sysconf(_SC_NPROCESSORS_ONLN);
	policy = sched_getscheduler(0);
	printf("BlackHoleThread X Running CpuID, Policy ,PID and No. of CPUs: %d %d %d %d\n",cpuID,policy,pid,cpuN);
	sched_getaffinity(0,sizeof(cpu_set_t),&mask);
	printf("BlackHoleThread X CPU affinity :");	
	for(int i=0;i<cpuN;i++){
		printf("%d ",CPU_ISSET(i,&mask));
	}
	printf("\n");		
	//printf("ALL scheduling policies are: %d %d %d %d %d\n",SCHED_OTHER,SCHED_FIFO,SCHED_BATCH,SCHED_RR,SCHED_IDLE);
	cpuID = sched_getcpu();
	printf("BlackHoleThread X Changed CPU ID : %d\n",cpuID);
}
void Y(){
	int cpuN,policy,cpuID;
	cpu_set_t mask;
	pid_t pid;
	cpuID = sched_getcpu();
	pid = getpid();
	cpuN = sysconf(_SC_NPROCESSORS_ONLN);
	policy = sched_getscheduler(0);
	printf("BlackHoleThread Y Running CpuID, Policy ,PID and No. of CPUs: %d %d %d %d\n",cpuID,policy,pid,cpuN);
	sched_getaffinity(0,sizeof(cpu_set_t),&mask);
	printf("BlackHoleThread Y CPU affinity :");	
	for(int i=0;i<cpuN;i++){
		printf("%d ",CPU_ISSET(i,&mask));
	}
	printf("\n");		
	//printf("ALL scheduling policies are: %d %d %d %d %d\n",SCHED_OTHER,SCHED_FIFO,SCHED_BATCH,SCHED_RR,SCHED_IDLE);
	cpuID = sched_getcpu();
	printf("BlackHoleThread Y Changed CPU ID : %d\n",cpuID);
}
int main(int argc,char *argv[]){
	pthread_t tid1,tid2;
	pthread_create(&tid1,NULL,(void*)X,NULL);
	pthread_create(&tid1,NULL,(void*)Y,NULL);
	
	for(int i=1;i<=10;i++){		
		int cpuN,policy,cpuID;
		cpu_set_t mask;
		pid_t pid;
		cpuID = sched_getcpu();
		pid = getpid();
		cpuN = sysconf(_SC_NPROCESSORS_ONLN);
		policy = sched_getscheduler(0);
		printf("BlackholeMainThread Running CpuID, Policy ,PID and No. of CPUs: %d %d %d %d\n",cpuID,policy,pid,cpuN);
		sched_getaffinity(0,sizeof(cpu_set_t),&mask);
		printf("BlackholeMainThread CPU affinity :");	
		for(int i=0;i<cpuN;i++){
			printf("%d ",CPU_ISSET(i,&mask));
		}
		printf("\n");		
		//printf("ALL scheduling policies are: %d %d %d %d %d\n",SCHED_OTHER,SCHED_FIFO,SCHED_BATCH,SCHED_RR,SCHED_IDLE);
		cpuID = sched_getcpu();
		printf("BlackholeMainThread Changed CPU ID : %d\n",cpuID);
	}
			
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	return 0;	
}
