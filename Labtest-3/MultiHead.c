#define _GNU_SOURCE
#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/syscall.h>
#include<sched.h>

int result;
pthread_mutex_t key;

void Ittu(void *val){
	pthread_mutex_lock(&key);
	pid_t pid,threadID;
	pid = getpid();
	threadID = gettid();
	int cpu = sched_getcpu();
	int *x = val;
	result = x[0]+x[1];
	printf("Ittu PID :%d,TID :%d,result :%d running at CPU :%d\n",pid,threadID,result,cpu);
	pthread_mutex_unlock(&key);
}
void Bittu(void *val){
	pthread_mutex_lock(&key);
	pid_t pid,threadID;
	pid = getpid();
	threadID = gettid();
	int cpu = sched_getcpu();
	int *x = val;
	result = x[0]-x[1];
	printf("Bittu PID :%d,TID :%d,result :%d running at CPU :%d\n",pid,threadID,result,cpu);
	pthread_mutex_unlock(&key);
}
void Mittu(void *val){
	pthread_mutex_lock(&key);
	pid_t pid,threadID;
	pid = getpid();
	threadID = gettid();
	int cpu = sched_getcpu();
	int *x = val;
	result = x[0]*x[1];
	printf("Mittu PID :%d,TID :%d,result :%d running at CPU :%d\n",pid,threadID,result,cpu);
	pthread_mutex_unlock(&key);
}
int main(){
	int value[2];
	value[0] = 30;
	value[1] = 10;
	pthread_t tid1,tid2,tid3;
	pid_t pid,threadID;
	pid = getpid();
	threadID = gettid();
	int cpu = sched_getcpu();
	printf("MainThread PID :%d,TID :%d running at CPU :%d\n",pid,threadID,cpu);
	for(int i=1;i<=10;i++){
		pthread_create(&tid1,NULL,(void*)Ittu,(void *)value);
		pthread_create(&tid2,NULL,(void*)Bittu,(void *)value);
		pthread_create(&tid3,NULL,(void*)Mittu,(void *)value);
	}
	
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	pthread_join(tid3,NULL);
	return 0;
}
