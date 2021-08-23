#include<stdio.h>
#include<unistd.h>

int main(){
    pid_t pid,cpid;
    fork();
    fork();
    printf("HELLO");
    return 0;
}
