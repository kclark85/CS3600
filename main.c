#define _POSIX_C_SOURCE

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <cygwin/signal.h>
#include <sys/signal.h>
#include <assert.h>
#include <sys/unistd.h>
#include <cygwin/wait.h>
#include <sys/wait.h>

void handler(int signum){
    if(signum == SIGINT){
        printf("Interrupt caught");
    }
}

int main() {
    struct sigaction action;
    action.sa_handler = handler;
    sigemptyset (&action.sa_mask);
    action.sa_flags = SA_RESTART;
    assert (sigaction (SIGUSR1, &action, NULL) == 0);

    pid_t ChildZero = fork();
    int result;
    if (ChildZero < 0) {
        perror("fork() error");
        exit(-1);
    }
    else if (ChildZero == 0) {
        //child
        //printf("Child Process: %d \n Parent Process: %d \n", ChildZero, getppid());
        execl("./child", "child", getppid(), "1", (char *)NULL);
    }
    else{
        //parent
        waitpid(-1, &result, 0);
        //printf("%d \n", );
        printf("Process %d exited with status : %d", ChildZero, WEXITSTATUS(result));
        if(sigaction(SIGINT, &action, NULL) == -1 ){
            perror("SIGACTION");
        }
    }
}
