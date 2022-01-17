#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc,char *argv[]){
	char *pipepath;
	pid_t pid,ppid;
	pipepath = argv[1];
	int fd = open(pipepath,O_WRONLY);
	pid = getpid();
	ppid = getppid();
	char *msg = "Hello";
	char child[100],parent[100];
	sprintf(child,"%d",pid);
	sprintf(parent,"%d",ppid);
	char *val1 = strcat(child,parent);
	char *val2 = strcat(msg,val1);
	write(fd,val2,strlen(val2)+1);
	//write(fd,child,strlen(child)+1);
	//write(fd,parent,strlen(parent)+1);
	close(fd);
	//printf("%d %d",pid,ppid);
	return 0;
}
