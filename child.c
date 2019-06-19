#define _POSIX_C_SOURCE

#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <cygwin/signal.h>
#include <sys/signal.h>
#include <features.h>

//pid_t fork();


int main(int argc, char *argv[]){
    char * end;
    int ppid = strtol(argv[1], &end, 10);
    int sig = strtol(argv[2], &end, 10);
    kill(ppid,SIGINT);
    //int id = strtol(pid, NULL, 10);
//    printf("Child PID: %d \n Parent PID: %d \n", getpid(), getppid());
//    for(int i = 1; i <= n; i++){
//        printf("Process: %d %d \n", getpid(), i);
//    }
    if(sig == 1) {
        kill(ppid,SIGINT);
    }
    else if(sig == 2){
        kill(ppid,SIGQUIT);
    }
}

