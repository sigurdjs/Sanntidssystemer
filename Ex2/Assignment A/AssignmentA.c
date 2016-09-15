#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int global_variable = 0;

int main() {
    pid_t pid;
    int local_variable = 0;
    vfork();
    pid = getpid();
    for(int i = 0; i < 10; i++) {
        printf("Process ID: %d, Global value: %i, Local value: %i\n",pid,global_variable,local_variable);
        local_variable++;
        global_variable++;
    }
    return(0);
}

