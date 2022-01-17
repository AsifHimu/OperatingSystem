#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc,char *argv[]){
	for(int i=1;i<argc;i++){
		//char *pipepath;
		int status = mkfifo(argv[i],0666);
		if(status < 0){
			printf("ERROR IN MAKING NEW PIPE\n");
		}
	}
	return 0;		
}
