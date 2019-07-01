#define _POSIX_C_SOURCE 200809l

#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/signal.h>
#include <features.h>
#include <assert.h>
#include <stdbool.h>
#include "syscall.h"
#include "eye2eh.c"


int main(int argc, char *argv[]){
    int pid = getpid();
    while(true){
        WRITESTRING("\nAwake in ")
        WRITEINT(pid,sizeof(pid))
        assert(sleep(1)==0);
    }
}
