#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc,char *argv[]){
	char *pipepath;
	pipepath = argv[1];
	int fd = open(pipepath,O_RDONLY);
	char buffer[200];
	read(fd,buffer,sizeof(buffer));
	close(fd);
	write(STDOUT_FILENO,buffer,strlen(buffer));
}
