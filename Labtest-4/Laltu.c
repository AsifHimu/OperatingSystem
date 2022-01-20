#define _GNU_SOURCE
#include <sys/ipc.h>
#include <stdio.h>
#include <sys/shm.h>
#include <string.h>
#include <sched.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include <sys/wait.h>
#include <sys/prctl.h>


int create_shared_memory(){
	key_t key;
	int shmID;
	key = ftok("check.c", 1);
	shmID = shmget(key, 1024, IPC_CREAT | 0666);
	return shmID;
}
void write_to_shm(int x){
	int shmID = create_shared_memory();
	char *str = shmat(shmID, NULL, 0);
	char num[100];
	sprintf(num, "%d", x);
	strcpy(str, num);
	shmdt(str);
}
int read_from_shm(){
	int shmID = create_shared_memory();
	char *str = shmat(shmID, NULL, 0);
	int num = (int) strtol(str, (char **)NULL, 10);
	shmdt(str);

	return num;
}
int main(){
	sem_t sem;
	int a,b,result=0;
    scanf("%d%d",&a,&b);

    write_to_shm(result);
	sem_init(&sem, 0, 1);

    pid_t cpid1, cpid2, cpid3;
    cpid1 = fork();

    if (cpid1 == 0) {
    	pid_t pid = getpid();
		result = read_from_shm();
		int cpu = sched_getcpu();
		printf("Ittu PID: %u,Running at CORE-%d result: %d\n",pid,cpu, result);
		result = a+b;
		printf("Ittu PID: %u,Running at CORE-%d result: %d\n",pid,cpu, result);
        write_to_shm(result);
    }
    else {
        cpid2 = fork();
        if (cpid2 == 0){
        	pid_t pid = getpid();
            result = read_from_shm();
            int cpu = sched_getcpu();
            printf("Bittu PID: %u,Running at CORE-%d result: %d\n",pid,cpu,result);
            result = a-b;
            printf("Bittu PID: %u,Running at CORE-%d result: %d\n",pid,cpu,result);
            write_to_shm(result);
        }
        else {
            cpid3 = fork();
            if (cpid3 == 0){
            	pid_t pid = getpid();
                result = read_from_shm();
                int cpu = sched_getcpu();
                printf("Mittu PID: %u,Running at CORE-%d result: %d\n",pid,cpu,result);
                result = a*b;
                printf("Mittu PID: %u,Running at CORE-%d result: %d\n",pid,cpu,result);
                write_to_shm(result);
            }
            else{
            	pid_t pid = getpid();
            	int cpu = sched_getcpu();
                printf("Laltu PID: %u, Running at CORE-%d result: %d\n",pid,cpu,result);
            }
        }
    }
    return 0;
}

