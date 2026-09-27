#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t pids[5];
    int status;

    //create five child processes
    for (int i = 0; i < 5; i++) {
        pids[i] = fork();
        if (pids[i] == 0) {
            //child process
            printf("Child %d with PID %d\n", i + 1, getpid());
            _exit(0); //exit child process
        }
    }

    //parent process
    for (int i = 0; i < 5; i++) {
        waitpid(pids[i], &status, 0);
        printf("Child %d (PID %d) exited with status %d\n", i + 1, pids[i], WEXITSTATUS(status));
    }
    return 0;
}