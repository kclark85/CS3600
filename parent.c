#define _POSIX_C_SOURCE 200809

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/signal.h>
#include <assert.h>
#include <sys/unistd.h>
#include <sys/wait.h>
#include "syscall.h"
#include "eye2eh.c"

void handler(int signum){
    if (signum == SIGCHLD) {
        WRITESTRING("Exit status: ")
        WRITEINT(signum, sizeof(signum))

    }
    else {
        WRITESTRING("Unexpected signal: ")
        WRITEINT(signum,sizeof(signum))
    }
    exit(0);
}

int main(int argc, char *argv[]) {
    struct sigaction action;
    action.sa_handler = handler;
    sigemptyset (&action.sa_mask);
    action.sa_flags = SA_RESTART | SA_NOCLDSTOP;

    assert (sigaction (SIGCHLD, &action, NULL) == 0);
    assert (sigaction (SIGINT, &action, NULL)== 0);

    pid_t ChildZero = fork();
    int result;
    if (ChildZero < 0) {
        perror("fork() error");
        exit(-1);
    }
    else if (ChildZero == 0) {
        //child
        //printf("Child Process: %d \n Parent Process: %d \n", ChildZero, getppid());
        execl("./child", "child", (char *)0);
        perror("execl");
        return -1;
    }
    else{
        //parent
        int cpid = ChildZero;
        for(int i = 0; i < 5; i++) {
            WRITESTRING("\nParent stopping child\n")
            assert (kill(cpid, SIGSTOP) == 0);
            //assert (kill(getpid(), SIGCONT) == 0);
            assert(sleep(2)==0);
            WRITESTRING("\nParent starting child\n")
            assert (kill(cpid, SIGCONT) == 0);
            //assert (kill(getpid(), SIGSTOP) == 0);
            assert(sleep(2)==0);

        }
        WRITESTRING("\n Parent stopping child (for good)\n")
        assert(kill(cpid, SIGINT) == 0);
        assert(waitpid(-1, &result, 0) != -1);
//        assert(printf("Process %d exited with status : %d", ChildZero, WEXITSTATUS(result)) !=0);
    }
    pause();
}